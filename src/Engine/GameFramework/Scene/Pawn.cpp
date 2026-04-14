// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Pawn.h"

#include "Engine/GameFramework/Scene/Camera.h"

//...

namespace Brahmanda
{
	void Pawn::Construct(const ObjectTransform& InTransform)
	{
		CameraViewData ViewData = {};
		PawnCamera = CreateSubobject<WorldCamera>(ViewData, ORTHOGRAPHIC_CAM);
	}

	void Pawn::Init()
	{

	}

	void Pawn::SetupInput(InputManager* InputMgr)
	{

	}
}