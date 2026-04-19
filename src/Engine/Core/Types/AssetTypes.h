// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

//...

namespace Brahmanda
{
	struct Vector4;
	struct TextureHandle;

	struct Sprite2D
	{
		TextureHandle SpriteTex;
		Vector4 UV;
		uint64_t SortKey;

		void SetSortKey(uint8_t InLayer, uint32_t InOrder, uint16_t InTexID, uint16_t InEntityID)
		{
			SortKey = 0u;

			SortKey |= (uint64_t)InLayer << 56;
			SortKey |= (uint64_t)InOrder << 32;
			SortKey |= (uint64_t)InTexID << 16;
			SortKey |= (uint64_t)InEntityID;
		}
	};
}