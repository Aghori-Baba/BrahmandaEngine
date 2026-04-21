// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <array>
#include <memory>
#include <type_traits>
#include <cassert>

#include "LayerContextData.h"
#include "Engine/Core/Types/RenderableTypes.h"
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
	struct Sprite2D;

	template<typename T>
	class ComponentContainer;

	class WorldLayer
	{
	public:

		enum class RenderGroup
		{
			Screen = 0,
			UI,
			Foreground,
			Midground,
			Background,
			COUNT
		};

		enum DirtyBytes : uint8_t
		{
			Transform = 1 << 0,		// position/rotation/scale
			Visibility = 1 << 1,	// generic visible/hidden toggle
			Material = 1 << 2,
			Texture = 1 << 3,
			Light = 1 << 4,

			RenderState = 1 << 5,	// batching/sort related
			Geometry = 1 << 6,		// mesh changed (3D)
			Reserved = 1 << 7
		};

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
			DirtyFlag |= 1 << 0;

			return EntityPtr;
		}

		void ReserveWorldSize(size_t InSize);
		void RegisterRenderables();
		void RegisterEntity(WorldEntity& InEntity);
		void UpdateEntityCache();
		void RegisterForCycle(WorldEntity* InEntity);
		std::vector<WorldEntity*>& GetCycleEnabledEntities();
		void UpdateForRender();

		inline uint8_t GetDirtyFlag() const;
		void MarkWorldDirty();
		//std::vector<RenderItem2D>& GetRenderables();

		bool GetIsLoaded() const;
		bool GetIsVisible() const;

		void SetAssetManager(AssetManager* InRef);
		CameraManager* GetCameraManager() const;

	public:

		EntityManager EntityMgr;

	protected:

		AssetManager* AssetManagerRef = nullptr;
		InputManager* InputMgr = nullptr;
		CameraManager* CameraMgr = nullptr;
		EntityInitializer EntityInitData;

	private:

		bool bIsLoaded = false;
		bool bIsVisible = false;
		uint32_t EntityCount = 0u;
		uint8_t DirtyFlag = 0u;

		std::vector<std::unique_ptr<WorldEntity>> WorldEntities;
		std::vector<WorldEntity*> CycleEnabledEntities;
		std::vector<Entity> Entities;
		//RenderGroup2D Renderables;
		//std::vector<RenderItem2D*> SortedItems;
		//std::vector<ItemProxy2D> RenderCommands;
		//std::array<std::vector<RenderItem2D>, static_cast<size_t>(WorldLayer::RenderGroup::COUNT)> RenderBucket;

		//ComponentContainer<Sprite2D>* TextureContainer = nullptr;
		//ComponentContainer<ObjectTransform>* TransformContainer = nullptr;
	};
}