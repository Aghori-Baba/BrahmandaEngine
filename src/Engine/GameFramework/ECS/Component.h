// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include "Entity.h"
#include "TypeID.h"

//...

namespace Brahmanda
{
	class Component
	{
	public:

		Component() = default;
		~Component() = default;
	};

	class IContainerBridge
	{
	public:

		static TypeID GetNextID()
		{
			static TypeID CurrentID = 0;
			return CurrentID++;
		}

		template<typename T>
		static TypeID GetTypeID()
		{
			static TypeID ID = GetNextID();
			return ID;
		}

		virtual void Interface() = 0;
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
			return Dense[Sparse[InEntity.ID]];
		}

		bool HasComponent(Entity InEntity)
		{
			uint32_t _id = InEntity.ID;
			return _id < Sparse.size() && Sparse[_id] != INVALID_INDEX;
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
		}

		const std::vector<T>& GetAllComponents() const
		{
			return Dense;
		}

		const std::vector<Entity>& GetAllEntities() const
		{
			return Entities;
		}

		void Interface() override {}

	private:

		std::vector<T> Dense;
		std::vector<Entity> Entities;
		std::vector<uint32_t> Sparse;
	};
}