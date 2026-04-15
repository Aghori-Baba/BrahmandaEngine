// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <memory>

#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/ECS/ComponentHandle.h"
#include "Engine/GameFramework/Scene/CameraData.h"
#include "Engine/GameFramework/Scene/Camera.h"

//...

namespace Brahmanda
{
	class GameCamera;
	class WorldCamera;

	class CameraManager
	{
	public:

		CameraManager(const CameraViewData& InView);
		CameraManager() = default;

		~CameraManager();

		void Init();
		void Cycle(float DeltaTime);
		void Shutdown();

		GameCamera* GetActiveCamera() const;
		void SetActiveCamera(const ComponentHandle<WorldCamera>& InCam);

	protected:

		void CreatePrimaryCamera();

	private:

		CameraViewData CamData{};
		ComponentHandle<WorldCamera> ActiveCamera = {};
		std::unique_ptr<GameCamera> PrimaryCamera;
	};
}