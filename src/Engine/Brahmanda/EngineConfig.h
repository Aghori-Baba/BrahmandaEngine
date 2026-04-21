// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

//...

namespace Brahmanda::Config
{
	namespace Engine
	{
		constexpr const char* NAME = "Brahmanda Engine";
		constexpr const char* VERSION = "0.01A";
	}

	namespace Rendering
	{
		constexpr size_t MAX_RENDERQUEUE_SIZE = 2000u;
		constexpr size_t MAX_DRAW_CALLS = 2048u;
	}
}