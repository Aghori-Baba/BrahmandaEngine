// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "CameraManager.h"


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
		if (ActiveCamera.IsValid())
		{
			PrimaryCamera->UpdateView(ActiveCamera.ReadOnly().GetViewData());
		}
	}

	void CameraManager::Shutdown()
	{

	}

	void CameraManager::CreatePrimaryCamera()
	{

	}

	GameCamera* CameraManager::GetPrimaryCamera() const
	{
		return PrimaryCamera.get();
	}

	void CameraManager::SetActiveCamera(const ComponentHandle<WorldCamera>& InCam)
	{
		ActiveCamera = InCam;
	}
}