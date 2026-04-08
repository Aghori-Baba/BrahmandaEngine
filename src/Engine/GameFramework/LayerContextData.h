// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

//...

namespace Brahmanda
{
	class AssetManager;
	class InputManager;
	class CameraManager;
	class SessionMaster;

	struct LayerContextData
	{
		AssetManager* AssetMgr = nullptr;
		InputManager* InputMgr = nullptr;
		CameraManager* CameraMgr = nullptr;
		SessionMaster* CurrentSession = nullptr;
	};
}