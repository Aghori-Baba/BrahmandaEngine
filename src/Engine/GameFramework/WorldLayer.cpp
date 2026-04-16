// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "WorldLayer.h"

#include <algorithm>

#include "Engine/Core/Types/RenderableTypes.h"
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

		ComponentContainer<Sprite2D>* _texCont = EntityMgr.GetContainerByType<Sprite2D>();
		ComponentContainer<ObjectTransform>* _transformCont = EntityMgr.GetContainerByType<ObjectTransform>();

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

	void WorldLayer::RegisterRenderables()
	{
		Renderables.clear();

		_texCont = EntityMgr.GetContainerByType<Sprite2D>();
		_transformCont = EntityMgr.GetContainerByType<ObjectTransform>();

		if (_texCont && _transformCont)
		{
			auto& _texDense = _texCont->GetAllComponents();
			auto& _texEntities = _texCont->GetAllEntities();

			for (uint32_t i = 0; i < _texDense.size(); i++)
			{
				Entity _e = _texEntities[i];

				auto& _tex = _texDense[i].SpriteTex;
				auto& _transform = _transformCont->GetComponent(_e);
				Renderables.emplace_back(_tex, &_transform);
			}

			std::sort(Renderables.begin(), Renderables.end(), [](const RenderData& a, const RenderData& b) { return a.Tex.GetID() < b.Tex.GetID(); });
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
		for (auto& It : Renderables)
		{
			InQueue.Submit(It);
		}

		//if (_texCont && _transformCont)
		//{
		//	auto& _texDense = _texCont->GetAllComponents();
		//	auto& _texEntities = _texCont->GetAllEntities();

		//	for (uint32_t i = 0; i < _texDense.size(); i++)
		//	{
		//		Entity _e = _texEntities[i];

		//		auto& _tex = _texDense[i].SpriteTex;
		//		auto& _transform = _transformCont->GetComponent(_e);
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