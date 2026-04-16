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
		RayCamera.offset = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
	}

	void GameCamera2D::UpdateView(const CameraViewData& InView)
	{
		RayCamera.target = { InView.ViewTarget.X,InView.ViewTarget.Y };
		RayCamera.rotation = InView.Rotation;
		RayCamera.zoom = InView.Zoom;
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

	void GameCamera2D::SetOffset(Vector2&& InOffset)
	{
		RayCamera.offset = { InOffset.X, InOffset.Y };
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

	void GameCamera3D::SetOffset(Vector2&& InOffset)
	{
		//TODO: Support 3D Offset
	}

	ECameraType WorldCamera::GetCameraType() const
	{
		return CameraType;
	}

	void WorldCamera::UpdateCameraView(const CameraViewData& InView)
	{
		ViewData = InView;
	}

	void WorldCamera::UpdateCameraLocation(const Vector3& InLoc)
	{
		ViewData.ViewTarget = InLoc;
	}

	void WorldCamera::SetCameraZoom(float InVal)
	{
		ViewData.Zoom = InVal;
	}

	const CameraViewData& WorldCamera::GetViewData()
	{
		return ViewData;
	}
}