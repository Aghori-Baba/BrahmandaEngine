// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "InputManager.h"
#include "GameFramework/Scene/Pawn.h"
#include "Systems/CameraManager.h"

//...

namespace Brahmanda
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::Construct(CameraManager* InCamMgr)
	{
		CamMgr = InCamMgr;
	}

	void InputManager::HandleInput(float DeltaTime)
	{
		float PosX = 0.f;
		float PosY = 0.f;
		float Mul = 5.f;

		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			Mul = 8.f;
		}
		if (IsKeyReleased(KEY_LEFT_SHIFT))
		{
			Mul = 5.f;
		}

		if (IsKeyDown(KEY_W))
		{
			PosY += -1.f * Mul * DeltaTime;
		}
		if (IsKeyDown(KEY_S))
		{
			PosY += 1.f * Mul * DeltaTime;
		}
		if (IsKeyDown(KEY_D))
		{
			PosX += 1.f * Mul * DeltaTime;
		}
		if (IsKeyDown(KEY_A))
		{
			PosX += -1.f * Mul *DeltaTime;
		}

		PawnTransformHandle.Edit().Translate(Vector3(PosX, PosY, 0.f));
		//if (PrimaryPawn)
		//{
		//	//PrimaryPawn->AddMovement(Vector3(PosX, PosY, 0.f));
		//	//PawnTransformHandle.Modify(Vector3(PosX, PosY, 0.f));
		//}
	}

	void InputManager::PossessPawn(Pawn* InTarget)
	{
		if (InTarget)
		{
			PrimaryPawn = InTarget;
			PrimaryPawn->SetupInput(this);

			CamMgr->SetActiveCamera(PrimaryPawn->GetComponentHandleByClass<WorldCamera>());
			PawnTransformHandle = PrimaryPawn->GetComponentHandleByClass<ObjectTransform>();
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