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
		CameraViewData ViewData = {};
		ViewData.ViewTarget = {0.f, 0.f, 0.f};
		ViewData.Zoom = 1.f;
		PrimaryCamera = std::make_unique<GameCamera2D>(ViewData);
		PrimaryCamera->Init();
	}

	void CameraManager::Cycle(float DeltaTime)
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

	GameCamera* CameraManager::GetActiveCamera() const
	{
		return PrimaryCamera.get();
	}

	void CameraManager::SetActiveCamera(WorldCamera* InCam)
	{
		ActiveCamera = InCam;
	}
}