// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "CameraManager.h"

//...

namespace Brahmanda
{
	CameraManager::CameraManager()
	{

	}

	CameraManager::~CameraManager()
	{

	}

	GameCamera* CameraManager::GetActiveCamera() const
	{
		return ActiveCamera;
	}

	void CameraManager::SetActiveCamera(GameCamera* InCam)
	{
		ActiveCamera = InCam;
	}
}