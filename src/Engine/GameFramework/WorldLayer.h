// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <memory>
#include <type_traits>
#include <cassert>

#include "LayerContextData.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/Systems/EntityManager.h"

//...

namespace Brahmanda
{
	class RenderQueue;
	class AssetManager;
	struct Entity;
	struct RenderData;

	class WorldLayer
	{
	public:

		WorldLayer(const LayerContextData& InData);

		~WorldLayer();

		WorldLayer() = delete;
		WorldLayer(const WorldLayer&) = delete;
		WorldLayer& operator=(const WorldLayer&) = delete;
		WorldLayer(WorldLayer&&) = delete;
		WorldLayer& operator=(WorldLayer&&) = delete;

		void Load();
		void Unload();

		virtual void OnLoad();
		virtual void OnUnload();

		template<typename T, typename ...Args>
		inline T* SpawnEntity(Args && ...InArgs)
		{
			static_assert(std::is_base_of_v<Entity, T>, "T must be derived from Entity");

			std::unique_ptr<T> NewEntity = std::make_unique<T>(std::forward<Args>(InArgs)...);
			T* EntityPtr = NewEntity.get();
			Entities.emplace_back(std::move(NewEntity));

			return EntityPtr;
		}

		void RegisterRenderables();
		void RegisterEntity(Entity& InEntity);
		void SubmitForRender(RenderQueue& InQueue);

		bool GetIsLoaded() const;
		bool GetIsVisible() const;

		void SetAssetManager(AssetManager* InRef);
		//std::vector<Entity> Entities;

	protected:

		AssetManager* AssetManagerRef = nullptr;
		EntityManager EntityMgr;

	private:

		bool bIsLoaded = false;
		bool bIsVisible = false;

		std::vector<std::unique_ptr<Entity>> Entities;
		std::vector<RenderData> Renderables;
	};
}