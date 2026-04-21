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
		_loc = TransformComp->GetLocation();

		PawnCamera->UpdateCameraLocation(_loc);
	}

	void Pawn::SetupInput(InputManager* InputMgr)
	{

	}

	void Pawn::AddMovement(const Vector3& InValue)
	{
		float _sum = InValue.X + InValue.Y + InValue.Z;
		if (_sum > 0.f)
		{
			TransformComp.Modify(InValue);
		}
	}

	void Pawn::AddMovement(const Vector3&& InValue)
	{
		TransformComp.Modify(InValue);
	}
}