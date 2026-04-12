// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>

//...

namespace Brahmanda
{
	struct Entity
	{
	public:

		Entity(uint32_t InID, uint32_t InGen)
			: ID(InID), Generation(InGen)
		{

		}

		Entity() = default;
		~Entity() = default;

		uint32_t ID = 0u;
		uint32_t Generation = 0u;
	};
}