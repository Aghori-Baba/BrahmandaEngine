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
		void RenderFrame(const FrameContextData& InContext);
		void EndRenderFrame();

		void ShutdownRenderer();

	private:

		AssetManager* AssetManagerRef = nullptr;
	};
}