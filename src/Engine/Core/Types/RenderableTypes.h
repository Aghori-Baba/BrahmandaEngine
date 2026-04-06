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

		RenderData(const TextureHandle& InTex, ObjectTransform* InTransform)
			: Tex(InTex), Transform(InTransform)
		{

		}

		GeometryHandle Geo;
		TextureHandle Tex;

		ObjectTransform* Transform = nullptr;

		//To be extended further as per requirement
	};

	class RenderQueue
	{
	public:

		RenderQueue() {};
		~RenderQueue() {};

		void ReserveSize(size_t InCount = 1000)
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

		const std::vector<RenderData>& GetRenderItems() const
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
}