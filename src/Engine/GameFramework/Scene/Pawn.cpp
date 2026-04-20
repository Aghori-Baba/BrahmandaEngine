// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Pawn.h"

#include "Engine/GameFramework/Scene/Camera.h"

//...

namespace Brahmanda
{
	void Pawn::Construct(const ObjectTransform& InTransform)
	{
		WorldEntity::Construct(InTransform);

		CameraViewData ViewData = {};
		PawnCamera = CreateSubobject<WorldCamera>(ViewData, ORTHOGRAPHIC_CAM);
	}

	void Pawn::Init()
	{
		WorldEntity::Init();


	}

	void Pawn::Cycle(float DeltaTime)
	{
		Vector3 _loc;
		_loc.X = TransformComp.Get().Pos[0];
		_loc.Y = TransformComp.Get().Pos[1];

		PawnCamera->UpdateCameraLocation(_loc);
	}

	void Pawn::SetupInput(InputManager* InputMgr)
	{

	}

	void Pawn::AddMovement(const Vector3& InValue)
	{
		TransformComp.Get().Pos[0] = InValue.X;
		TransformComp.Get().Pos[1] = InValue.Y;
		TransformComp.Get().Pos[2] = InValue.Z;
	}

	void Pawn::AddMovement(const Vector3&& InValue)
	{
		TransformComp->Translate(InValue);
	}
}