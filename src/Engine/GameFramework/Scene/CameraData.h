// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/Core/Types/CustomTypes.h"

//...

namespace Brahmanda
{
	enum class ECameraType
	{
		ECT_NONE,
		ECT_2DCamera,
		ECT_3DCamera
	};

	inline constexpr auto ORTHOGRAPHIC_CAM = ECameraType::ECT_2DCamera;
	inline constexpr auto PERSPECTIVE_CAM = ECameraType::ECT_3DCamera;

	struct CameraViewData
	{
		Vector3 ViewTarget = {};
		float Rotation = 0.f;
		float Zoom = 0.f;
	};
}