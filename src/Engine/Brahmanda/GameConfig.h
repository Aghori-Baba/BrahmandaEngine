// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

//...

/* GAME CONFIG
 *	
 *	This is a central file for storing common game configurations that will be needed during development.
 *
 */

namespace Brahmanda::Config
{
	namespace World
	{
		//Change this value to modify max number of World Layers Mandala can contain
		constexpr size_t MAX_WORLD_LAYER_COUNT = 8u;

		enum ERenderLayer
		{
			ERL_Screen = 0,
			ERL_UI,
			ERL_Foreground,
			ERL_Midground,
			ERL_Background,
			ERL_COUNT
		};

		//uint8_t EnumToBytes()
	}
}
