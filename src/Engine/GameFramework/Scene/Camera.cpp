// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Camera.h"

//...

namespace Brahmanda
{
	void GameCamera2D::Init()
	{
		RayCamera.target = { ViewData.ViewTarget.X, ViewData.ViewTarget.Y };
		RayCamera.rotation = ViewData.Rotation;
		RayCamera.zoom = ViewData.Zoom;
	}

	void GameCamera2D::UpdateView(const CameraViewData& InView)
	{
		RayCamera.target = { InView.ViewTarget.X,InView.ViewTarget.Y };
	}

	void GameCamera2D::Reset()
	{

	}

	Camera2D* GameCamera2D::Get2DCamera()
	{
		return &RayCamera;
	}

	Camera3D* GameCamera2D::Get3DCamera()
	{
		return nullptr;
	}

	ECameraType GameCamera::GetCameraType()
	{
		return CameraType;
	}

	void GameCamera3D::Init()
	{
		RayCamera.target = { ViewData.ViewTarget.X, ViewData.ViewTarget.Y, ViewData.ViewTarget.Z };
	}

	void GameCamera3D::UpdateView(const CameraViewData& InView)
	{
		RayCamera.target = { InView.ViewTarget.X,InView.ViewTarget.Y, InView.ViewTarget.Z };
	}

	void GameCamera3D::Reset()
	{

	}

	Camera2D* GameCamera3D::Get2DCamera()
	{
		return nullptr;
	}

	Camera3D* GameCamera3D::Get3DCamera()
	{
		return &RayCamera;
	}

	ECameraType WorldCamera::GetCameraType() const
	{
		return CameraType;
	}

	void WorldCamera::UpdateCameraView(const CameraViewData& InView)
	{
		ViewData = InView;
	}

	CameraViewData WorldCamera::GetViewData()
	{
		return ViewData;
	}
}