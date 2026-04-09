// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/ECS/Component.h"

//...

namespace Brahmanda
{
	class Entity;

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
		ComponentRegistry<T>* GetRegistryByType()
		{
			TypeID ID = IRegistryBridge::GetTypeID<T>();

			auto _It = RegistryStorage.find(ID);
			if (_It == RegistryStorage.end())
			{
				return nullptr;
			}

			return static_cast<ComponentRegistry<T>*>(_It->second.get());
		}

	private:

		std::vector<uint32_t> FreeList;
		std::vector<uint32_t> Generations;

		std::unordered_map<TypeID, std::unique_ptr<IRegistryBridge>> RegistryStorage;
	};
}