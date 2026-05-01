// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <array>
#include <unordered_map>
#include <tuple>
#include <cstdint>

#include "Brahmanda/GameConfig.h"
#include "Engine/Core/Types/RenderableTypes.h"

//...

namespace Brahmanda
{
	using namespace Config;

	struct ProxyIndex
	{
		World::ERenderLayer Layer;
		uint32_t Index;
	};

	class SceneProxy
	{
	public:

		SceneProxy();
		~SceneProxy();

		void Construct();
		void Init();
		void Shutdown();
	};

	class SceneProxy2D
	{
	public:

		SceneProxy2D();
		~SceneProxy2D();

		void Construct();
		void Init();
		void Shutdown();

		const std::array<std::vector<ItemProxy2D>, World::ERenderLayer::ERL_COUNT>& GetProxyData() const;
		void AddProxy(ObjectTransform& InTransform, uint32_t InID, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey);
		void UpdateProxyTransform(uint32_t InID, const ObjectTransform& InTransform);
		void UpdateProxySprite(uint32_t InID, const TextureHandle& InTex, const Vector4& InUV);
		void TryAddProxy(ObjectTransform& InTransform, uint32_t InID, TextureHandle InTex, Vector4 InUV, uint64_t InSortKey);
		void SortAll();
		void SortLayer(World::ERenderLayer InLayer);
		void ClearAllLayers();

	private:

		std::array<std::vector<ItemProxy2D>, World::ERenderLayer::ERL_COUNT> ProxyData;
		std::unordered_map<uint32_t, std::tuple<World::ERenderLayer, uint32_t>> Lookup;
		//std::array<std::vector<uint32_t>, World::ERenderLayer::ERL_COUNT> Mapping;
		//std::unordered_map<uint32_t, std::vector<ProxyIndex>> Mapping;
	};
}