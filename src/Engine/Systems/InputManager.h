// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <memory>

//...

namespace Brahmanda
{
	class Entity;
	class Pawn;

	class InputManager
	{
	public:

		InputManager();
		~InputManager();

		void PossessPawn(Pawn* InTarget);
		const Pawn* GetPossessedPawn() const;
		void EjectPawn();

		void EnableInput(Entity* InTarget);
		void DisableInput(Entity* InTarget);

	private:

		Pawn* PrimaryPawn = nullptr;
		Pawn* DefaultPawn = nullptr;
		std::vector<Entity*> ControlledEntities;
	};
}