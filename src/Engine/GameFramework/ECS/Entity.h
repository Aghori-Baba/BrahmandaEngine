// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/Core/Types/HandleTypes.h"

//...

namespace Brahmanda
{
	class Entity
	{
	public:

		Entity(const ObjectTransform& InTransform)
			: Transform(InTransform)
		{

		}

		Entity() = default;
		~Entity() = default;

		TextureHandle Tex = {};
		GeometryHandle Geo = {};

		ObjectTransform Transform = {};

		uint32_t ID;
	};
}