// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cassert>
#include "EntityManager.h"
#include "Engine/GameFramework/ECS/Entity.h"

//...

namespace Brahmanda
{
	void EntityManager::Init()
	{
		FreeList.reserve(1000u);
		Generations.reserve(1000u);

		TypeID _id = IContainerBridge::GetTypeID<ObjectTransform>();
		ContainerList.emplace(_id, std::make_unique<ComponentContainer<ObjectTransform>>());

		ComponentContainer<ObjectTransform>* TransformList = GetContainerByType<ObjectTransform>();
	}

	Entity EntityManager::CreateNewEntity()
	{
		uint32_t _id = 0u;

		if (Generations.size() >= INVALID_ID)
		{
			assert(false && "Max Entity reached");
			return Entity::InvalidEntity();
		}

		if (!FreeList.empty())
		{
			_id = FreeList.back();
			FreeList.pop_back();
		}
		else
		{
			_id = Generations.size();
			Generations.push_back(0u);
		}

		return Entity(_id, Generations[_id]);
	}

	void EntityManager::DestroyEntity(Entity InEntity)
	{
		uint32_t _id = InEntity.ID;
		Generations[_id]++;
		FreeList.push_back(_id);
	}

	bool EntityManager::IsEntityAlive(Entity InEntity)
	{
		return Generations[InEntity.ID] == InEntity.Generation;
	}

	void EntityManager::Shutdown()
	{

	}
}