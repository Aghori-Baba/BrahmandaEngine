// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <memory>
#include <type_traits>
#include <cassert>

#include "LayerContextData.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/Systems/EntityManager.h"
#include "Engine/GameFramework/Scene/WorldEntityInitializer.h"

//...

namespace Brahmanda
{
	class RenderQueue;
	class AssetManager;
	struct WorldEntity;
	struct RenderData;
	struct EntityInitializer;

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

		void Construct();
		virtual void OnConstruct();

		void Load();
		void Unload();

		virtual void OnLoad();
		virtual void OnUnload();

		template<typename T, typename ...Args>
		inline T* SpawnEntity(const ObjectTransform& InTransform, Args && ...InArgs)
		{
			static_assert(std::is_base_of_v<WorldEntity, T>, "T must be derived from Entity");

			Entity _e = EntityMgr.CreateNewEntity();
			EntityInitData.EntityHandle = _e;
			Entities.push_back(_e);

			std::unique_ptr<T> NewEntity = std::make_unique<T>(EntityInitData, std::forward<Args>(InArgs)...);
			T* EntityPtr = NewEntity.get();
			EntityPtr->Construct(InTransform);
			WorldEntities.emplace_back(std::move(NewEntity));

			return EntityPtr;
		}

		void RegisterRenderables();
		void RegisterEntity(WorldEntity& InEntity);
		void SubmitForRender(RenderQueue& InQueue);

		bool GetIsLoaded() const;
		bool GetIsVisible() const;

		void SetAssetManager(AssetManager* InRef);

	protected:

		AssetManager* AssetManagerRef = nullptr;
		InputManager* InputMgr = nullptr;
		EntityManager EntityMgr;
		EntityInitializer EntityInitData;

	private:

		bool bIsLoaded = false;
		bool bIsVisible = false;
		uint32_t EntityCount = 0;

		std::vector<std::unique_ptr<WorldEntity>> WorldEntities;
		std::vector<Entity> Entities;
		std::vector<RenderData> Renderables;
	};
}