// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/Core/Types/CustomTypes.h"
#include "CameraData.h"
#include "raylib.h"

//...

namespace Brahmanda
{
	class GameCamera
	{
	public:

		GameCamera(ECameraType InType, const CameraViewData& InView)
			: CameraType(InType), ViewData(InView)
		{

		}

		GameCamera() = delete;

		~GameCamera() = default;

		virtual void Init() = 0;
		virtual void UpdateView(const CameraViewData& InView) = 0;
		virtual void Reset() = 0;

		ECameraType GetCameraType();

		virtual Camera2D* Get2DCamera() = 0;
		virtual Camera3D* Get3DCamera() = 0;

	protected:

		ECameraType CameraType = ECameraType::ECT_NONE;
		CameraViewData ViewData = {};

	private:

	};

	class GameCamera2D : public GameCamera
	{
		GameCamera2D(const CameraViewData& InView)
			: GameCamera(ECameraType::ECT_2DCamera, InView)
		{

		}

		void Init() override;
		void UpdateView(const CameraViewData& InView) override;
		void Reset() override;

		Camera2D* Get2DCamera() override;
		Camera3D* Get3DCamera() override;

	private:

		Camera2D RayCamera = {};
	};

	class GameCamera3D : public GameCamera
	{
		GameCamera3D(const CameraViewData& InView)
			: GameCamera(ECameraType::ECT_3DCamera, InView)
		{

		}

		void Init() override;
		void UpdateView(const CameraViewData& InView) override;
		void Reset() override;

		Camera2D* Get2DCamera() override;
		Camera3D* Get3DCamera() override;

	private:

		Camera3D RayCamera = {};
	};

	class WorldCamera
	{
	public:

		WorldCamera(const CameraViewData& InView, ECameraType InType)
			: ViewData(InView), CameraType(InType)
		{

		}

		~WorldCamera() = default;

		ECameraType GetCameraType() const;
		void UpdateCameraView(const CameraViewData& InView);
		CameraViewData GetViewData();

	private:

		ECameraType CameraType = ECameraType::ECT_NONE;
		CameraViewData ViewData = {};
	};
}