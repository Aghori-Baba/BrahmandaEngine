// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <cassert>
#include <unordered_map>

#include "Entity.h"
#include "TypeID.h"

//...

namespace Brahmanda
{
	using ENTITY_ID = uint32_t;
	using DIRTY_INDEX = uint32_t;

	enum EComponentState : uint8_t
	{
		ECS_NONE = 0u,
		ECS_Created = 1 << 0,
		ECS_Updated = 1 << 1,
	};

	class Component
	{
	public:

		Component() = default;
		~Component() = default;
	};

	struct Entry
	{
		Entry(ENTITY_ID InID, DIRTY_INDEX InIndex)
			: ID(InID), Index(InIndex)
		{

		}

		uint32_t ID;
		uint32_t Index;
	};

	class IContainerBridge
	{
	public:

		static TypeID GetNextID()
		{
			static TypeID CurrentID = 0u;
			return CurrentID++;
		}

		template<typename T>
		static TypeID GetTypeID()
		{
			static TypeID ID = GetNextID();
			return ID;
		}

		virtual void Interface() = 0u;
	};

	template<typename T>
	class ComponentContainer : public IContainerBridge
	{
	public:

		void AddComponent(Entity InEntity, T InComp)
		{
			if (HasComponent(InEntity))
			{
				return;
			}

			uint32_t _i = InEntity.ID;

			if (_i >= Sparse.size())
			{
				Sparse.resize(_i + 1, INVALID_INDEX);
			}

			uint32_t _di = Dense.size();
			Dense.push_back(InComp);
			Entities.push_back(InEntity);
			Sparse[_i] = _di;
		}

		template<typename... Args>
		T& CreateNewComponent(Entity InEntity, Args&&... InArgs)
		{
			uint32_t _id = InEntity.ID;

			assert(_id != INVALID_ID && "Invalid Entity ID");

			if (HasComponent(InEntity))
			{
				return Dense[Sparse[_id]];
			}

			if (_id >= Sparse.size())
			{
				Sparse.resize(_id + 1, INVALID_INDEX);
			}

			uint32_t _i = static_cast<uint32_t>(Dense.size());
			Dense.emplace_back(std::forward<Args>(InArgs)...);
			Entities.emplace_back(InEntity);
			Sparse[_id] = _i;

			return Dense[_i];
		}

		T& GetComponent(Entity InEntity)
		{
			assert(InEntity.ID != INVALID_ID && "Invalid Entity ID");
			return Dense[Sparse[InEntity.ID]];
		}

		bool HasComponent(Entity InEntity)
		{
			uint32_t _id = InEntity.ID;
			return _id < INVALID_ID && _id < Sparse.size() && Sparse[_id] != INVALID_INDEX;
		}

		void DeleteComponent(Entity InEntity)
		{
			uint32_t _i = InEntity.ID;
			if (_i >= Sparse.size())
			{
				return;
			}

			uint32_t _dense = Sparse[_i];
			if (_dense == INVALID_INDEX)
			{
				return;
			}

			uint32_t _last = static_cast<uint32_t>(Dense.size() - 1);
			Entity _back = Entities[_last];

			std::swap(Dense[_dense], Dense[_last]);
			std::swap(Entities[_dense], Entities[_last]);

			Sparse[_back.ID] = _dense;

			Dense.pop_back();
			Entities.pop_back();
			Sparse[_i] = INVALID_INDEX;

			//Updating Dirty List:
			auto It1 = DirtyMapping.find(_i);
			if (It1 != DirtyMapping.end())
			{
				uint32_t _idx = It1->second;
				uint32_t _lastIdx = DirtyList.size() - 1;

				if (_idx != _lastIdx)
				{
					DirtyList[_idx] = DirtyList[_lastIdx];
					DirtyMapping[DirtyList[_idx].ID] = _idx;
				}

				DirtyList.pop_back();
				DirtyMapping.erase(It1);
			}

			if (_dense != _last)
			{
				auto It2 = DirtyMapping.find(_back.ID);
				if (It2 != DirtyMapping.end())
				{
					uint32_t _idx = It2->second;

					DirtyList[_idx].Index = _dense;
					DirtyMapping[DirtyList[_idx].ID] = _idx;
				}
			}
		}

		const std::vector<T>& GetAllComponents() const
		{
			return Dense;
		}

		const std::vector<Entity>& GetAllEntities() const
		{
			return Entities;
		}

		const std::vector<uint32_t>& GetAllSparse() const
		{
			return Sparse;
		}

		const std::vector<Entry>& GetAllDirty()
		{
			return DirtyList;
		}

		void MarkComponentDirty(ENTITY_ID InID)
		{
			ENTITY_ID _idx = Sparse[InID];

			DirtyList.emplace_back(InID, _idx);
			DirtyMapping[InID] = _idx;
		}

		void RemoveDirtyItemAtEnd()
		{
			if (DirtyList.size() == 0)
			{
				return;
			}

			Entry _entry = DirtyList.back();
			DirtyMapping.erase(_entry.ID);
			DirtyList.pop_back();
		}

		void ReserveSize(size_t InSize)
		{
			Dense.reserve(InSize);
		}

		void Interface() override {}

	private:

		std::vector<T> Dense;
		std::vector<Entity> Entities;
		std::vector<ENTITY_ID> Sparse;
		std::vector<Entry> DirtyList;
		std::unordered_map<ENTITY_ID, DIRTY_INDEX> DirtyMapping;
	};
}