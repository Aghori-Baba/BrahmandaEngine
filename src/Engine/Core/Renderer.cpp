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
		//if (InContext.ActiveCamera->GetCameraType() == ECameraType::ECT_2DCamera)
		//{
		//	BeginMode2D(InContext.ActiveCamera->Get2DCamera());
		//}

		for (const auto& Item : InContext.PrimaryQueue.GetRenderItems())
		{
 			Texture& Tex = AssetManagerRef->GetTexture(Item.Tex);
			ObjectTransform* Transform = Item.Transform;
			DrawTexturePro(Tex, { 0, 0, (float)Tex.width, (float)Tex.height }, { Transform->Pos[0], Transform->Pos[1], 100, 100 }, {}, Transform->Rot[0], WHITE);
		}
	}

	void Brahmanda::Renderer::EndRenderFrame()
	{
		rlImGuiEnd();

		EndDrawing();
	}
}