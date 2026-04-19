// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Engine.h"

#include "IGame.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/Systems/EntityManager.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Types/RenderableTypes.h"
#include "Engine/Systems/Logger.h"

//...

namespace Brahmanda
{
	Engine::Engine()
	{

	}

	bool Engine::InitEngine()
	{
		Logger::InitLogger();

		GlobalAssetManager = std::make_unique<AssetManager>();
		GlobalAssetManager->Init();
		EntityManagerRef = std::make_unique<EntityManager>();
		EntityManagerRef->Init();
		RendererRef = std::make_unique<Renderer>();
		RendererRef->InitRenderer(GlobalAssetManager.get());

		RenderQueueRef = std::make_unique<RenderQueue>();
		RenderQueueRef->ReserveSize(Config::Rendering::MAX_RENDERQUEUE_SIZE);
		RenderQueueRef->Clear();

		if (GameRef)
		{
			GameInitalizerData InitData;
			InitData.AssetMgr = GlobalAssetManager.get();
			InitData.EntityMgr = EntityManagerRef.get();

			GameRef->Construct(InitData);
			GameRef->Init();

			return true;
		}

		return false;
	}

	void Engine::CycleEngine(float DeltaTime)
	{
		RenderQueue& Queue = *RenderQueueRef;
		Queue.ReserveSize();
		Queue.Clear();

		RendererRef->BeginRenderFrame();

		FrameContextData FrameContext(Queue);
		GameRef->Cycle(DeltaTime, FrameContext);

		RendererRef->RenderFrame(FrameContext);

		RendererRef->EndRenderFrame();
	}

	void Engine::ShutdownEngine()
	{
		if (GameRef)
		{
			GameRef->Shutdown();
		}

		GlobalAssetManager->Shutdown();
		EntityManagerRef->Shutdown();
	}

	void Engine::SetGame(IGame* InGame)
	{
		GameRef = InGame;
	}

	AssetManager* Engine::GetGameAssetManager() const
	{
		return GlobalAssetManager.get();
	}

	Engine::~Engine()
	{

	}
}