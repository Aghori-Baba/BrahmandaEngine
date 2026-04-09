// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include "Entity.h"

//...

namespace Brahmanda
{
	struct Entity;

	using TypeID = uint32_t;

	class Component
	{
	public:

		Component() = default;
		~Component() = default;
	};

	class IRegistryBridge
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
	class ComponentRegistry : public IRegistryBridge
	{
	public:

		void AddComponent(Entity InEntity, T InComp)
		{
			uint32_t _i = InEntity.ID;

			if (_i >= Sparse.size())
			{
				Sparse.resize(_i + 1, UINT32_MAX);
			}

			uint32_t _di = Dense.size();
			Dense.push_back(InComp);
			Entities.push_back(_i);
			Sparse[_i] = _di;
		}

		T& GetComponent(Entity InEntity)
		{
			return Dense[Sparse[InEntity.ID]];
		}

		bool HasComponent(Entity InEntity)
		{
			return InEntity.ID < Sparse.size && Sparse[InEntity.ID] != UINT32_MAX;
		}

		void DeleteComponent(Entity InEntity)
		{
			uint32_t _i = InEntity.ID;
			uint32_t _dense = Sparse[_i];

			if (_dense == UINT32_MAX)
			{
				return;
			}
			
			uint32_t _last = Dense.size() - 1;
			uint32_t _back = Entities[_last];
			std::swap(Dense[_dense], Dense[_last]);
			std::swap(Entities[_dense], Entities[_last]);

			Sparse[Entities[_dense]] = _dense;

			Dense.pop_back();
			Entities.pop_back();
			Sparse[_i] = UINT32_MAX;
		}

		std::vector<T>& GetAllComponents() const
		{
			return Dense;
		}

		void Interface() override {}

	private:

		std::vector<T> Dense;
		std::vector<uint32_t> Entities;
		std::vector<uint32_t> Sparse;
	};
}