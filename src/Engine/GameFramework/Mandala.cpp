// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Mandala.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Core/Types/RenderableTypes.h"
#include "Engine/Systems/CameraManager.h"

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
		CameraManagerRef = std::make_unique<CameraManager>(ViewData);

		OnInit();

		if (!bIsSessionCreated)
		{
			StartNewSession<SessionMaster>();
		}

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

		for (auto& It : Collection.GetLayerList())
		{
			if (It && It->GetIsLoaded())
			{
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