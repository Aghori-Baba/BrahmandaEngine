// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "InputManager.h"
#include "GameFramework/Scene/Pawn.h"

//...

namespace Brahmanda
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::HandleInput()
	{

	}

	void InputManager::PossessPawn(Pawn* InTarget)
	{
		if (InTarget)
		{
			PrimaryPawn = InTarget;
			PrimaryPawn->SetupInput(this);
		}
	}

	const Pawn* InputManager::GetPossessedPawn() const
	{
		return PrimaryPawn;
	}

	void InputManager::EjectPawn()
	{

	}

	void InputManager::EnableInput(WorldEntity* InTarget)
	{

	}

	void InputManager::DisableInput(WorldEntity* InTarget)
	{

	}
}