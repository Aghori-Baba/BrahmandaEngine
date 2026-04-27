// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <memory>

#include "Engine/GameFramework/ECS/ComponentHandle.h"

//...

namespace Brahmanda
{
	class WorldEntity;
	class CameraManager;
	class Pawn;
	struct ObjectTransform;

	class InputManager
	{
	public:

		InputManager();
		~InputManager();

		void Construct(CameraManager* InCamMgr);
		virtual void HandleInput(float DeltaTime);

		void PossessPawn(Pawn* InTarget);
		const Pawn* GetPossessedPawn() const;
		void EjectPawn();

		void EnableInput(WorldEntity* InTarget);
		void DisableInput(WorldEntity* InTarget);

	private:

		Pawn* PrimaryPawn = nullptr;
		Pawn* DefaultPawn = nullptr;
		std::vector<WorldEntity*> ControlledEntities;
		ComponentHandle<ObjectTransform> PawnTransformHandle;

		CameraManager* CamMgr = nullptr;
	};
}