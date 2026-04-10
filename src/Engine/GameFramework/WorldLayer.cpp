// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "WorldLayer.h"

#include "Engine/Core/Types/RenderableTypes.h"
#include "Engine/Core/Types/HandleTypes.h"
#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/ECS/Entity.h"

//...

namespace Brahmanda
{
	WorldLayer::WorldLayer(const LayerContextData& InData)
	{
		AssetManagerRef = InData.AssetMgr;
	}

	WorldLayer::~WorldLayer()
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
		for (auto& _e : Entities)
		{
			if (_e->Tex.GetIsVisible())
			{
				Renderables.emplace_back(_e->Tex, &_e->Transform);
			}
		}
	}

	void WorldLayer::RegisterEntity(Entity& InEntity)
	{
		if (InEntity.Tex.GetIsVisible())
		{
			Renderables.emplace_back(InEntity.Tex, &(InEntity.Transform));
		}
	}

	void WorldLayer::SubmitForRender(RenderQueue& InQueue)
	{
		for (auto It : Renderables)
		{
			InQueue.Submit(It);
		}

		//for (auto& It : Entities)
		//{
		//	if (It)
		//	{
		//		TextureHandle& t = It->Tex;
		//		if (!t.GetIsVisible())
		//		{
		//			continue;
		//		}

		//		RenderData Data;
		//		Data.Tex = t;
		//		Data.Transform = &It->Transform;
		//		InQueue.Submit(std::move(Data));
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