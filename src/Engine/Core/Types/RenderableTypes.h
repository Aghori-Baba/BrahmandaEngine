// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include "HandleTypes.h"
#include "CustomTypes.h"

//...

namespace Brahmanda
{
	class GameCamera;

	struct RenderData
	{
		RenderData() = default;

		RenderData(ObjectTransform* InTransform, const TextureHandle& InTex, const Vector4 InUV)
			: Transform(InTransform), Tex(InTex), UV(InUV)
		{

		}

		TextureHandle Tex;
		ObjectTransform* Transform;
		Vector4 UV;

		//To be extended further as per requirement
	};

	class RenderQueue
	{
	public:

		RenderQueue() {};
		~RenderQueue() {};

		void ReserveSize(size_t InCount = 20000u)
		{
			RenderItems.reserve(InCount);
		}

		void Clear()
		{
			RenderItems.clear();
		}

		void Submit(const RenderData& InData)
		{
			RenderItems.emplace_back(InData);
		}

		template<typename... Args>
		void Submit(Args&&... args)
		{
			RenderItems.emplace_back(std::forward<Args>(args)...);
		}

		std::vector<RenderData>& GetRenderItems()
		{
			return RenderItems;
		}
		
	private:

		std::vector<RenderData> RenderItems;
	};

	struct FrameContextData
	{
		FrameContextData(RenderQueue& InQueue) :
			PrimaryQueue(InQueue)
		{

		}

		FrameContextData(const FrameContextData&) = default;
		FrameContextData operator=(const FrameContextData&) = delete;

		RenderQueue& PrimaryQueue;
		GameCamera* ActiveCamera = nullptr;

		//To be expanded further as per requirement
	};

	struct Proxy2D
	{
		TextureHandle Tex;
		Vector4 UV;
	};

	struct RenderItem2D
	{
		RenderItem2D(ObjectTransform* InTransform, TextureHandle InTex, Vector4 InUV)
			: Transform(InTransform), Proxy{InTex, InUV}
		{

		}

		ObjectTransform* Transform;
		Proxy2D Proxy;
	};

	struct RenderGroup2D
	{
		void Add(ObjectTransform* InTransform, TextureHandle InTex, Vector4 InUV)
		{
			Items.emplace_back( InTransform, InTex, InUV );
		}

		std::vector<RenderItem2D> Items;
	};
}