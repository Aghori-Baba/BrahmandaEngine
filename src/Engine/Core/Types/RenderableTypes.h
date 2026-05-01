// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include "HandleTypes.h"
#include "CustomTypes.h"

//...

namespace Brahmanda
{
	class GameCamera;
	class SceneProxy;
	class SceneProxy2D;

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

		SceneProxy* SceneProx3D = nullptr;
		SceneProxy2D* SceneProx2D = nullptr;

		//To be expanded further as per requirement
	};

	struct Proxy2D
	{
		TextureHandle Tex;
		Vector4 UV;
	};

	struct RenderItem2D
	{
		RenderItem2D(ObjectTransform* InTransform, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey)
			: Transform(InTransform), Proxy{InTex, InUV}, SortKey(InSortKey)
		{

		}

		ObjectTransform* Transform;
		Proxy2D Proxy;
		uint64_t SortKey = 0u;
	};

	struct ItemProxy2D
	{
		ItemProxy2D(ObjectTransform& InTransform, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey, uint32_t InID)
			: tex(InTex), uv(InUV), sortKey(InSortKey), id(InID)
		{
			x = InTransform.Pos[0];
			y = InTransform.Pos[1];
			sx = InTransform.Scale[0];
			sy = InTransform.Scale[1];
			r = InTransform.Rot[0];
		}

		void Update(const ObjectTransform& InTransform)
		{
			x = InTransform.Pos[0];
			y = InTransform.Pos[1];
			sx = InTransform.Scale[0];
			sy = InTransform.Scale[1];
			r = InTransform.Rot[0];
		}

		void Update(const TextureHandle& InTex, const Vector4& InUV)
		{
			tex = InTex;
			uv = InUV;
		}

		float x, y;
		float sx, sy;
		float r;
		TextureHandle tex;
		Vector4 uv;
		uint64_t sortKey;
		uint32_t id;
	};

	struct RenderGroup2D
	{
		void Add(ObjectTransform* InTransform, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey)
		{
			Items.emplace_back( InTransform, InTex, InUV, InSortKey);
		}

		std::vector<RenderItem2D> Items;
		std::vector<RenderItem2D*> SortedItems;
	};
}