// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "EntityManager.h"
#include "Engine/GameFramework/ECS/Entity.h"

//...

namespace Brahmanda
{
	void EntityManager::Init()
	{
		FreeList.reserve(1000u);
		Generations.reserve(1000u);
	}

	Entity EntityManager::CreateNewEntity()
	{
		uint32_t _ID = 0u;

		if (!FreeList.empty())
		{
			_ID = FreeList.back();
			FreeList.pop_back();
		}
		else
		{
			_ID = Generations.size();
			Generations.push_back(0u);
		}

		return Entity(_ID, Generations[_ID]);
	}

	void EntityManager::DestroyEntity(Entity InEntity)
	{
		Generations[InEntity.ID]++;
		FreeList.push_back(InEntity.ID);
	}

	bool EntityManager::IsEntityAlive(Entity InEntity)
	{
		return Generations[InEntity.ID] == InEntity.Generation;
	}

	void EntityManager::Shutdown()
	{
		TypeID _ID = IRegistryBridge::GetTypeID<ObjectTransform>();
		RegistryStorage.emplace(_ID, std::make_unique<ComponentRegistry<ObjectTransform>>());

		ComponentRegistry<ObjectTransform>* TransformList = GetRegistryByType<ObjectTransform>();
	}
}