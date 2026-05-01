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

	void SceneProxy2D::AddProxy(ObjectTransform& InTransform, uint32_t InID, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey)
	{
		uint8_t _layer = (uint8_t)(InSortKey >> 56);
		_layer = (World::ERenderLayer::ERL_COUNT - 1u) - _layer;
		if (_layer < World::ERenderLayer::ERL_COUNT)
		{
			ProxyData[_layer].emplace_back(InTransform, InTex, InUV, InSortKey, InID);
			Lookup.try_emplace(InID, static_cast<World::ERenderLayer>(_layer), static_cast<uint32_t>(ProxyData[_layer].size() - 1));
		}
	}

	void SceneProxy2D::UpdateProxyTransform(uint32_t InID, const ObjectTransform& InTransform)
	{
		auto It = Lookup.find(InID);
		if (It != Lookup.end())
		{
			auto& [_layer, _idx] = It->second;
			auto& _itm = ProxyData[_layer][_idx];
			_itm.Update(InTransform);
		}
	}

	void SceneProxy2D::UpdateProxySprite(uint32_t InID, const TextureHandle& InTex, const Vector4& InUV)
	{
		auto It = Lookup.find(InID);
		if (It != Lookup.end())
		{
			auto& [_layer, _idx] = It->second;
			auto& _itm = ProxyData[_layer][_idx];
			_itm.Update(InTex, InUV);
		}
	}

	void SceneProxy2D::TryAddProxy(ObjectTransform& InTransform, uint32_t InID, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey)
	{
		auto It = Lookup.find(InID);
		if (It != Lookup.end())
		{
			return;
		}

		AddProxy(InTransform, InID, InTex, InUV, InSortKey);
	}

	void SceneProxy2D::SortAll()
	{
		for (auto& _layer : ProxyData)
		{
			std::sort(_layer.begin(), _layer.end(), [](const ItemProxy2D& a, const ItemProxy2D& b)
				{
					return a.tex.GetID() < b.tex.GetID();
				});
		}

		Lookup.clear();
		for (uint8_t i = 0u; i < World::ERenderLayer::ERL_COUNT; i++)
		{
			uint32_t _index = 0;
			for (auto& _item : ProxyData[i])
			{
				Lookup.try_emplace(_item.id, static_cast<World::ERenderLayer>(i), _index);
				_index++;
			}
		}
	}

	void SceneProxy2D::SortLayer(World::ERenderLayer InLayer)
	{
		auto& _layer = ProxyData[InLayer];

		for (auto& _layer : ProxyData)
		{
			std::sort(_layer.begin(), _layer.end(), [](const ItemProxy2D& a, const ItemProxy2D& b)
				{
					return a.tex.GetID() < b.tex.GetID();
				});
		}

		uint32_t _index = 0u;
		for (auto& _item : ProxyData[InLayer])
		{
			Lookup[_item.id] = { InLayer, _index };
		}
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