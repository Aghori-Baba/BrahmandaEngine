// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <memory>
#include "Types/RenderableTypes.h"

//...

namespace Brahmanda
{
	class AssetManager;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void InitRenderer(AssetManager* InRef);

		void BeginRenderFrame();
		void RenderPass2D(GameCamera* InCam, const SceneProxy2D* InSceneProxy);
		void RenderPass3D(GameCamera* InCam, const SceneProxy* InSceneProxy);
		void EndRenderFrame();

		void ShutdownRenderer();


	private:

		AssetManager* AssetManagerRef = nullptr;
	};
}