// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "WorldEntity.h"
#include "Engine/Core/Types/CustomTypes.h"

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

	const Entity WorldEntity::GetEntityHandle() const
	{
		return EntityHandle;
	}

	WorldEntity::~WorldEntity()
	{

	}
}