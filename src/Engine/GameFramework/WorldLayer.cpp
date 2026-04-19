// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "WorldLayer.h"

#include <algorithm>

#include "Engine/Core/Types/HandleTypes.h"
#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/Core/Types/AssetTypes.h"
#include "Engine/GameFramework/Scene/WorldEntity.h"

//...

namespace Brahmanda
{
	WorldLayer::WorldLayer(const LayerContextData& InData)
	{
		AssetManagerRef = InData.AssetMgr;
		InputMgr = InData.InputMgr;
	}

	WorldLayer::~WorldLayer()
	{

	}

	void WorldLayer::Construct()
	{
		EntityInitData.EntityMgr = &EntityMgr;
		EntityInitData.OwningWorld = this;
	}

	void WorldLayer::OnConstruct()
	{

	}

	void WorldLayer::Load()
	{
		bIsLoaded = true;
		Entities.reserve(5000);
		SortedItems.reserve(5000);
		RenderCommands.clear();
		RenderCommands.reserve(Renderables.Items.size());

		ComponentContainer<Sprite2D>* TextureContainer = EntityMgr.GetContainerByType<Sprite2D>();
		ComponentContainer<ObjectTransform>* TransformContainer = EntityMgr.GetContainerByType<ObjectTransform>();

		OnLoad();
	}

	void WorldLayer::OnLoad()
	{

	}

	void WorldLayer::Unload()
	{
		OnUnload();

		bIsLoaded = false;
	}

	void WorldLayer::OnUnload()
	{

	}

	void WorldLayer::ReserveWorldSize(size_t InSize)
	{
		TransformContainer->ReserveSize(InSize);
	}

	void WorldLayer::RegisterRenderables()
	{
		Renderables.Items.clear();

		TextureContainer = EntityMgr.GetContainerByType<Sprite2D>();
		TransformContainer = EntityMgr.GetContainerByType<ObjectTransform>();

		if (TextureContainer && TransformContainer)
		{
			auto& _texDense = TextureContainer->GetAllComponents();
			auto& _texEntities = TextureContainer->GetAllEntities();

			for (uint32_t i = 0; i < _texDense.size(); i++)
			{
				Entity _e = _texEntities[i];

				auto& _sprite = _texDense[i];
				auto& _transform = TransformContainer->GetComponent(_e);
				Renderables.Add(&_transform, _sprite.SpriteTex, _sprite.UV, _sprite.SortKey);
			}

			//std::sort(Renderables.Items.begin(), Renderables.Items.end(), 
			//	[](const RenderItem2D& a, const RenderItem2D& b) 
			//	{ 
			//		return a.Proxy.Tex.GetID() < b.Proxy.Tex.GetID(); 
			//	});
		}
	}

	void WorldLayer::RegisterEntity(WorldEntity& InEntity)
	{

	}

	void WorldLayer::UpdateEntityCache()
	{

	}

	void WorldLayer::RegisterForCycle(WorldEntity* InEntity)
	{
		CycleEnabledEntities.push_back(InEntity);
	}

	std::vector<WorldEntity*>& WorldLayer::GetCycleEnabledEntities()
	{
		return CycleEnabledEntities;
	}

	void WorldLayer::SubmitForRender(RenderQueue& InQueue)
	{
		SortedItems.clear();

		for(auto& It : Renderables.Items)
		{
			SortedItems.push_back(&It);
		}

		std::sort(SortedItems.begin(), SortedItems.end(),
			[](const RenderItem2D* a, const RenderItem2D* b)
			{
				return a->SortKey < b->SortKey;
			});

		for (auto& It : SortedItems)
		{
			InQueue.Submit(RenderData(It->Transform, It->Proxy.Tex, It->Proxy.UV));
		}

		//if (TextureContainer && TransformContainer)
		//{
		//	auto& _texDense = TextureContainer->GetAllComponents();
		//	auto& _texEntities = TextureContainer->GetAllEntities();

		//	for (uint32_t i = 0; i < _texDense.size(); i++)
		//	{
		//		Entity _e = _texEntities[i];

		//		auto& _tex = _texDense[i].SpriteTex;
		//		auto& _transform = TransformContainer->GetComponent(_e);
		//		InQueue.Submit(RenderData(_tex, &_transform));
		//	}
		//}
	}

	bool WorldLayer::GetIsLoaded() const
	{
		return bIsLoaded;
	}

	bool WorldLayer::GetIsVisible() const
	{
		return bIsVisible;
	}

	void WorldLayer::SetAssetManager(AssetManager* InRef)
	{
		AssetManagerRef = InRef;
	}
}