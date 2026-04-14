// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <memory>

//...

namespace Brahmanda
{
	class WorldEntity;
	class CameraManager;
	class Pawn;

	class InputManager
	{
	public:

		InputManager();
		~InputManager();

		void Construct();
		virtual void HandleInput();

		void PossessPawn(Pawn* InTarget);
		const Pawn* GetPossessedPawn() const;
		void EjectPawn();

		void EnableInput(WorldEntity* InTarget);
		void DisableInput(WorldEntity* InTarget);

	private:

		Pawn* PrimaryPawn = nullptr;
		Pawn* DefaultPawn = nullptr;
		std::vector<WorldEntity*> ControlledEntities;

		CameraManager* CamMgr = nullptr;
	};
}