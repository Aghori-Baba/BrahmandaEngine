// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "WorldLayer.h"

#include "Engine/Core/Types/RenderableTypes.h"
#include "Engine/Core/Types/HandleTypes.h"
#include "Engine/Core/Types/CustomTypes.h"
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

		auto* _texCont = EntityMgr.GetContainerByType<TextureHandle>();
		auto* _transformCont = EntityMgr.GetContainerByType<ObjectTransform>();

		auto& _texDense = _texCont->GetAllComponents();
		auto& _texEntities = _texCont->GetAllEntities();

		for (uint32_t i = 0; i < _texDense.size(); i++)
		{
			Entity _e = _texEntities[i];

			auto& _tex = _texDense[i];
			auto& _transform = _transformCont->GetComponent(_e);
			Renderables.emplace_back(_tex, _transform);
		}
	}

	void WorldLayer::RegisterEntity(WorldEntity& InEntity)
	{

	}

	void WorldLayer::SubmitForRender(RenderQueue& InQueue)
	{
		for (auto It : Renderables)
		{
			InQueue.Submit(It);
		}
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