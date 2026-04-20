// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "SceneProxy.h"

#include <algorithm>

//...

namespace Brahmanda
{
	SceneProxy::SceneProxy()
	{

	}

	SceneProxy::~SceneProxy()
	{

	}

	void SceneProxy::Construct()
	{

	}

	void SceneProxy::Init()
	{

	}

	const std::array<std::vector<ItemProxy2D>, World::ERenderLayer::ERL_COUNT>& SceneProxy2D::GetProxyData() const
	{
		return ProxyData;
	}

	void SceneProxy2D::AddProxy(ObjectTransform& InTransform, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey)
	{
		uint8_t _layer = (uint8_t)(InSortKey >> 56);
		_layer = (World::ERenderLayer::ERL_COUNT - 1u) - _layer;
		if (_layer >= 0u)
		{
			ProxyData[_layer].emplace_back(InTransform, InTex, InUV, InSortKey);
		}
	}

	void SceneProxy2D::SortAll()
	{
		for (auto& _layer : ProxyData)
		{
			std::sort(_layer.begin(), _layer.end(), [](const ItemProxy2D& a, ItemProxy2D& b)
				{
					return a.tex.GetID() < b.tex.GetID();
				});
		}
	}

	void SceneProxy2D::SortLayer(World::ERenderLayer InLayer)
	{
		auto& _layer = ProxyData[InLayer];


	}

	void SceneProxy2D::ClearAllLayers()
	{
		for (auto& It : ProxyData)
		{
			It.clear();
		}
	}

	void SceneProxy::Shutdown()
	{

	}

	SceneProxy2D::SceneProxy2D()
	{

	}

	SceneProxy2D::~SceneProxy2D()
	{

	}
}