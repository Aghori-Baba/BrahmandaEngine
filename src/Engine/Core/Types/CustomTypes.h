// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>

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

	struct Vector4
	{
		constexpr Vector4() = default;

		constexpr Vector4(float x, float y, float z, float w)
			: X(x), Y(y), Z(z), W(w)
		{

		}

		float X = 0.f;
		float Y = 0.f;
		float Z = 0.f;
		float W = 0.f;
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

		uint8_t DirtyFlag = 0u;

		Vector3 GetLocation() const
		{
			return Vector3(Pos[0], Pos[1], Pos[2]);
		}

		Vector3 GetRotation() const
		{
			return Vector3(Rot[0], Rot[1], Rot[2]);
		}

		Vector3 GetScale() const
		{
			return Vector3(Scale[0], Scale[1], Scale[2]);
		}

		void GetLocationByRef(Vector3& OutVal) const
		{
			OutVal.X = Pos[0];
			OutVal.Y = Pos[1];
			OutVal.Z = Pos[2];
		}

		void GetRotationByRef(Vector3& OutVal) const
		{
			OutVal.X = Rot[0];
			OutVal.Y = Rot[1];
			OutVal.Z = Rot[2];
		}

		void GetScaleByRef(Vector3& OutVal) const
		{
			OutVal.X = Scale[0];
			OutVal.Y = Scale[1];
			OutVal.Z = Scale[2];
		}

		void Translate(Vector3 InValue)
		{
			Pos[0] += InValue.X;
			Pos[1] += InValue.Y;
			Pos[2] += InValue.Z;

			DirtyFlag |= 1 << 0;
		}

		void Translate2D(Vector2 InValue)
		{
			Pos[0] += InValue.X;
			Pos[1] += InValue.Y;

			DirtyFlag |= 1 << 0;
		}

		void Rotate(Vector3 InValue)
		{
			Rot[0] += InValue.X;
			Rot[1] += InValue.Y;
			Rot[2] += InValue.Z;

			DirtyFlag |= 1 << 1;
		}

		void AddScale(Vector3 InValue)
		{
			Scale[0] += InValue.X;
			Scale[1] += InValue.Y;
			Scale[2] += InValue.Z;

			DirtyFlag |= 1 << 2;
		}

		void SetLocation(Vector3 InValue)
		{
			Pos[0] = InValue.X;
			Pos[1] = InValue.Y;
			Pos[2] = InValue.Z;

			DirtyFlag |= 1 << 0;
		}

		void SetLocation2D(Vector2 InValue)
		{
			Pos[0] = InValue.X;
			Pos[1] = InValue.Y;

			DirtyFlag |= 1 << 0;
		}

		void SetRotation(Vector3 InValue)
		{
			Rot[0] = InValue.X;
			Rot[1] = InValue.Y;
			Rot[2] = InValue.Z;

			DirtyFlag |= 1 << 1;
		}

		void SetScale(Vector3 InValue)
		{
			Scale[0] = InValue.X;
			Scale[1] = InValue.Y;
			Scale[2] = InValue.Z;

			DirtyFlag |= 1 << 2;
		}

		void ClearDirtyFlag()
		{
			DirtyFlag = 0u;
		}

		//To be extended further as per requirement
	};
}