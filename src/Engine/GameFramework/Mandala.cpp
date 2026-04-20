// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Mandala.h"

#include <algorithm>

#include "Engine/Core/Types/RenderableTypes.h"
#include "Engine/GameFramework/Scene/Camera.h"
#include "Engine/GameFramework/Scene/WorldEntity.h"
#include "Engine/Core/Types/AssetTypes.h"
#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Systems/CameraManager.h"
#include "Engine/Systems/InputManager.h"

//...

namespace Brahmanda
{
	Mandala::Mandala()
	{

	}

	Mandala::~Mandala()
	{

	}

	void Mandala::Construct(ManadalaInitializerData Initializer)
	{
		AssetManager = Initializer.AssetMgr;
		LayerData.AssetMgr = AssetManager;
	}

	void Mandala::Init()
	{
		Logger::Info("Mandala - Init - Called from Base class!");

		CameraViewData ViewData;
		ViewData.ViewTarget = { 0.f, 0.f, 0.f };
		CameraManagerRef = std::make_unique<CameraManager>(ViewData);
		CameraManagerRef->Init();

		//GlobalData.reserve(15000u);

		OnInit();

		if (!bIsInputManagerCreated)
		{
			CreateInputManager<InputManager>();
		}
		if (!bIsSessionCreated)
		{
			StartNewSession<SessionMaster>();
		}

		LayerData.CameraMgr = CameraManagerRef.get();

		PostInit();
	}

	void Mandala::OnInit()
	{

	}

	void Mandala::PostInit()
	{

	}

	void Mandala::Cycle(float DeltaTime, FrameContextData& InContext)
	{
		OnCycle(DeltaTime);

		//GlobalData.clear();

		InputManagerRef->HandleInput(DeltaTime);
		CameraManagerRef->Cycle(DeltaTime);

 		InContext.ActiveCamera = CameraManagerRef->GetPrimaryCamera();

		for (auto& It : Collection.GetLayerList())
		{
			if (It && It->GetIsLoaded())
			{
				auto& _entities = It->GetCycleEnabledEntities();
				for (auto& _e : _entities)
				{
					_e->Cycle(DeltaTime);
				}

				//for (auto& _renderIt : It->GetRenderables())
				//{
				//	GlobalData.push_back(&_renderIt);
				//}
			}
		}
		
		InContext.SceneProx2D = &SceneProx2D;

		CheckUpdatedRenderables();

		//std::sort(GlobalData.begin(), GlobalData.end(),
		//[](const RenderItem2D* a, const RenderItem2D* b)
		//{
		//	return a->SortKey > b->SortKey;
		//});

		//for (auto& It : GlobalData)
		//{
		//	InContext.PrimaryQueue.Submit(It->Transform, It->Proxy.Tex, It->Proxy.UV);
		//}
	}

	void Mandala::OnCycle(float DeltaTime)
	{

	}

	void Mandala::GatherRenderables()
	{
		SceneProx2D.ClearAllLayers();

		for (auto& It : Collection.GetLayerList())
		{
			if (It && It->GetIsLoaded())
			{
				const auto& _sprList = It->EntityMgr.GetContainerByType<Sprite2D>();
				const auto& _transformList = It->EntityMgr.GetContainerByType<ObjectTransform>();

				auto& _texDense = _sprList->GetAllComponents();
				auto& _texEntities = _sprList->GetAllEntities();

				for (int i = 0; i < _texDense.size(); i++)
				{
					Entity _e = _texEntities[i];

					auto& _sprite = _texDense[i];
					auto& _transform = _transformList->GetComponent(_e);

					SceneProx2D.AddProxy(_transform, _e.ID, _sprite.SpriteTex, _sprite.UV, _sprite.SortKey);
				}
			}
		}

		SceneProx2D.SortAll();
	}

	void Mandala::CheckUpdatedRenderables()
	{
		for (auto& It : Collection.GetLayerList())
		{
			if (It && It->GetIsLoaded())
			{
				const auto& _transCont = It->EntityMgr.GetContainerByType<ObjectTransform>();
				const auto& _transforms = _transCont->GetAllComponents();
				const auto& _entities = _transCont->GetAllEntities();

				uint32_t _index = 0u;
				for (auto& _t : _transforms)
				{
					if (_t.DirtyFlag != 0u)
					{
						//World::ERenderLayer _l = 
						uint32_t _id = _entities[_index].ID;

						//SceneProx2D.UpdateProxy();
					}

					_index++;
				}
			}
		}
	}

	void Mandala::Shutdown()
	{
		OnShutdown();

		Logger::Info("Mandala - Shutdown - Called from Base class!");
	}

	void Mandala::OnShutdown()
	{

	}

	void Mandala::SetWorldConfig(const WorldConfig& InConfig)
	{

	}
}