// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <memory>

#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/Scene/CameraData.h"

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
		void SetActiveCamera(WorldCamera* InCam);

	protected:

		void CreatePrimaryCamera();

	private:

		CameraViewData CamData{};
		WorldCamera* ActiveCamera = nullptr;
		std::unique_ptr<GameCamera> PrimaryCamera;
	};
}