// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

//...

namespace Brahmanda
{
	struct Vector2
	{
		constexpr Vector2() = default;

		constexpr Vector2(float x, float y)
			: X(x), Y(y)
		{

		}

		float X = 0.f;
		float Y = 0.f;
	};

	struct Vector3
	{
		constexpr Vector3() = default;

		constexpr Vector3(float x, float y, float z)
			: X(x), Y(y), Z(z)
		{

		}

		float X = 0.f;
		float Y = 0.f;
		float Z = 0.f;
	};

	struct ObjectTransform
	{
		//Custom wrapper to support other data formats in future.
		//For now things will be simpler

		//Positions
		float Pos[3] = { 0.f, 0.f, 0.f };

		//Rotations
		float Rot[3] = { 0.f, 0.f, 0.f };

		//Scales
		float Scale[3] = { 1.f, 1.f, 1.f };

		//To be extended further as per requirement
	};
}