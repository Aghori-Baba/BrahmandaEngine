// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "CameraManager.h"

#include "Engine/GameFramework/Scene/Camera.h"

//...

namespace Brahmanda
{
	CameraManager::CameraManager(const CameraViewData& InView)
	{

	}

	CameraManager::~CameraManager()
	{

	}

	void CameraManager::Init()
	{

	}

	void CameraManager::Cycle()
	{
		if (ActiveCamera)
		{
			PrimaryCamera->UpdateView(ActiveCamera->GetViewData());
		}
	}

	void CameraManager::Shutdown()
	{

	}

	void CameraManager::CreatePrimaryCamera()
	{

	}

	WorldCamera* CameraManager::GetActiveCamera() const
	{
		return ActiveCamera;
	}

	void CameraManager::SetActiveCamera(WorldCamera* InCam)
	{
		ActiveCamera = InCam;
	}
}