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

		using PARENT = Pawn;

		Pawn(EntityInitializer InInitializer)
			: WorldEntity(InInitializer) {}

		void Construct(const ObjectTransform& InTransform) override;
		void Init() override;
		void Cycle(float DeltaTime) override;
		virtual void SetupInput(InputManager* InputMgr);

		void AddMovement(const Vector3& InValue);
		void AddMovement(const Vector3&& InValue);

	protected:

		ComponentHandle<WorldCamera> PawnCamera;
	};
}