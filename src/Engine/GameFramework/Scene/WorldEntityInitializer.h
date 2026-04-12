// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/ECS/Entity.h"

//...

namespace Brahmanda
{
	class Entity;
	class WorldLayer;
	class EntityManager;

	struct EntityInitializer
	{
		Entity EntityHandle = {};
		WorldLayer* OwningWorld = nullptr;
		EntityManager* EntityMgr = nullptr;
	};
}