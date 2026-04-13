// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>

//...

namespace Brahmanda
{
	constexpr uint32_t INVALID_ID = UINT32_MAX;

	struct Entity
	{
	public:

		Entity(uint32_t InID, uint32_t InGen)
			: ID(InID), Generation(InGen)
		{

		}

		static Entity InvalidEntity()
		{
			return Entity(INVALID_ID, INVALID_ID);
		}

		Entity() = default;
		~Entity() = default;

		uint32_t ID = INVALID_ID;
		uint32_t Generation = INVALID_ID;
	};
}