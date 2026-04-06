// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/Scene/Camera.h"
#include "Engine/Core/Types/CustomTypes.h"

//...

namespace Brahmanda
{
	class CameraManager
	{
	public:

		CameraManager();
		~CameraManager();

		GameCamera* GetActiveCamera() const;
		void SetActiveCamera(GameCamera* InCam);

	private:

		CameraViewData CamData{};
		GameCamera* ActiveCamera = nullptr;
	};
}