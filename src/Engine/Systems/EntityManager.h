// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Engine/Core/Types/CustomTypes.h"
#include "GameFramework/ECS/TypeID.h"
#include "Engine/GameFramework/ECS/Component.h"

//...

namespace Brahmanda
{
	struct Entity;

	class EntityManager
	{
	public:

		EntityManager() = default;
		~EntityManager() = default;

		void Init();
		void Shutdown();

		Entity CreateNewEntity();
		void DestroyEntity(Entity InEntity);
		bool IsEntityAlive(Entity InEntity);

		template<typename T>
		ComponentContainer<T>* GetContainerByType()
		{
  			TypeID ID = IContainerBridge::GetTypeID<T>();

			auto _It = ContainerList.find(ID);
			if (_It == ContainerList.end())
			{
				//TODO: Refactor into modern CPP standards
				std::unique_ptr<ComponentContainer<T>> _Container = std::make_unique<ComponentContainer<T>>();
				ComponentContainer<T>* _p = _Container.get();
				ContainerList.emplace(ID, std::move(_Container));
				return _p;
			}

			return static_cast<ComponentContainer<T>*>(_It->second.get());
		}

	private:

		std::vector<uint32_t> FreeList;
		std::vector<uint32_t> Generations;

		std::unordered_map<TypeID, std::unique_ptr<IContainerBridge>> ContainerList;
	};
}