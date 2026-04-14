// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <memory>

#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/Scene/WorldEntity.h"
#include "GameFramework/ECS/ComponentHandle.h"

//...

namespace Brahmanda
{
	class WorldCamera;
	class InputManager;

	class Pawn : public WorldEntity
	{
	public:

		Pawn(EntityInitializer InInitializer)
			: WorldEntity(InInitializer) {}

		void Construct(const ObjectTransform& InTransform) override;
		void Init() override;
		virtual void SetupInput(InputManager* InputMgr);

	protected:

		ComponentHandle<WorldCamera> PawnCamera;
	};
}