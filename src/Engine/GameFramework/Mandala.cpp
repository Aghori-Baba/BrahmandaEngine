// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Mandala.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Core/Types/RenderableTypes.h"
#include "Engine/Systems/CameraManager.h"
#include "Engine/GameFramework/Scene/Camera.h"
#include "Engine/Systems/InputManager.h"
#include "Engine/GameFramework/Scene/WorldEntity.h"

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

		InputManagerRef->HandleInput(DeltaTime);
		CameraManagerRef->Cycle(DeltaTime);

 		InContext.ActiveCamera = CameraManagerRef->GetActiveCamera();

		for (auto& It : Collection.GetLayerList())
		{
			if (It && It->GetIsLoaded())
			{
				auto& _entities = It->GetCycleEnabledEntities();
				for (auto& _e : _entities)
				{
					_e->Cycle(DeltaTime);
				}

				It->SubmitForRender(InContext.PrimaryQueue);
			}
		}
	}

	void Mandala::OnCycle(float DeltaTime)
	{

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