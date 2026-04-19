// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <array>

#include "Engine/Core/Types/RenderableTypes.h"

//...

namespace Brahmanda
{
	enum ERenderLayer
	{
		ERL_Screen = 0,
		ERL_UI,
		ERL_Foreground,
		ERL_Midground,
		ERL_Background,
		ERL_COUNT
	};

	class SceneProxy
	{
	public:

		SceneProxy();
		~SceneProxy();

		void Construct();
		void Init();
		void Shutdown();
	};

	class SceneProxy2D
	{
	public:

		SceneProxy2D();
		~SceneProxy2D();

		void Construct();
		void Init();
		void Shutdown();

		//void AddCommand();

	private:

		std::vector<RenderCommand2D> CommandQueue;
	};
}