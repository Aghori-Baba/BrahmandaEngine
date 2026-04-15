// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "WorldEntity.h"
#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/WorldLayer.h"

//...

namespace Brahmanda
{
	void WorldEntity::Construct(const ObjectTransform& InTransform)
	{
		TransformComp = CreateSubobject<ObjectTransform>();
		TransformComp.Get() = InTransform;

	}

	void WorldEntity::Init()
	{

	}

	void WorldEntity::Cycle(float DeltaTime)
	{

	}

	void WorldEntity::Shutdown()
	{

	}

	void WorldEntity::RegisterForCycle()
	{
		OwningWorld->RegisterForCycle(this);
	}

	const bool WorldEntity::GetCanCycle() const
	{
		return bCanRunCycle;
	}

	const Entity WorldEntity::GetEntityHandle() const
	{
		return EntityHandle;
	}

	WorldEntity::~WorldEntity()
	{

	}
}