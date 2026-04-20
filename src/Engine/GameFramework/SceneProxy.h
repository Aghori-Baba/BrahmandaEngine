// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <array>
#include <unordered_map>
#include <cstdint>

#include "Brahmanda/GameConfig.h"
#include "Engine/Core/Types/RenderableTypes.h"

//...

namespace Brahmanda
{
	using namespace Config;

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
		void UpdateProxy(World::ERenderLayer InLayer, uint32_t InID);
		void SortAll();
		void SortLayer(World::ERenderLayer InLayer);
		void ClearAllLayers();

	private:

		std::array<std::vector<ItemProxy2D>, World::ERenderLayer::ERL_COUNT> ProxyData;
		std::array<std::vector<uint32_t>, World::ERenderLayer::ERL_COUNT> Mapping;
	};
}