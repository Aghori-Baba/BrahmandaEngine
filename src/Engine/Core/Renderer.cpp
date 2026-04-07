// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Renderer.h"
#include "ModuleIncludes.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/GameFramework/Scene/Camera.h"

//...

namespace Brahmanda
{
	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Brahmanda::Renderer::InitRenderer(AssetManager* InRef)
	{
		AssetManagerRef = InRef;
		
	}

	void Brahmanda::Renderer::ShutdownRenderer()
	{

	}

	void Brahmanda::Renderer::BeginRenderFrame()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		rlImGuiBegin();
	}

	void Renderer::RenderFrame(const FrameContextData& InContext)
	{
		auto* Cam = InContext.ActiveCamera;
		bool bIsOrtho = false;
		bool bHasActiveCam = Cam != nullptr;
		// TODO: EMERGENCY CLEANUP NEEDED HERE
		auto* DrawCam = Cam->Get2DCamera();
		DrawCam->target = { 0.f ,0.f };
		DrawCam->rotation = 0.f;
		DrawCam->zoom = 1.f;

		DrawCam->offset = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };

		if (IsKeyDown(KEY_W)) DrawCam->target.x += 100.f;
		if (IsKeyDown(KEY_S)) DrawCam->target.x -= 100.f;
		if (IsKeyDown(KEY_D)) DrawCam->target.y += 100.f;
		if (IsKeyDown(KEY_A)) DrawCam->target.y -= 100.f;

		if (bHasActiveCam)
		{
			bIsOrtho = Cam->GetCameraType() == ORTHOGRAPHIC_CAM;

			if (bIsOrtho)
			{
				BeginMode2D(*(Cam->Get2DCamera()));
			}
			else
			{
				//TODO: 3D Mode not supported yet.
				//BeginMode3D(*(Cam->Get3DCamera()));
			}
		}

		for (const auto& Item : InContext.PrimaryQueue.GetRenderItems())
		{
 			Texture& Tex = AssetManagerRef->GetTexture(Item.Tex);
			ObjectTransform* Transform = Item.Transform;
			DrawTexturePro(Tex, { 0, 0, (float)Tex.width, (float)Tex.height }, { Transform->Pos[0], Transform->Pos[1], 100, 100 }, {0, 0}, Transform->Rot[0], WHITE);
		}

		if (bHasActiveCam)
		{
			if (bIsOrtho)
			{
				EndMode2D();
			}
			else
			{
				//TODO: 3D Mode not supported yet.
				//EndMode3D();
			}
		}
	}

	void Brahmanda::Renderer::EndRenderFrame()
	{
		rlImGuiEnd();

		EndDrawing();
	}
}