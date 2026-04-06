// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>

//...

namespace Brahmanda
{
	template<typename T>
	struct Signal
	{
		T SignalData{};
		uint32_t SignalID = 0U;
	};
}