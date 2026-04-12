// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "CoreIncludes.h"
#include "Engine/Brahmanda/EngineConfig.h"

//...

namespace Brahmanda
{
	class IGame;
	class AssetManager;
	class EntityManager;
	class Renderer;
	class RenderQueue;

	class Engine
	{
	public:
		Engine();
		~Engine();

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;

		bool InitEngine();
		void CycleEngine(float DeltaTime);
		void ShutdownEngine();

		void SetGame(IGame* InGame);
		AssetManager* GetGameAssetManager() const;

	private:

		IGame* GameRef = nullptr;
		std::unique_ptr<Brahmanda::AssetManager> GlobalAssetManager;
		std::unique_ptr<EntityManager> EntityManagerRef;
		std::unique_ptr<Renderer> RendererRef;
		std::unique_ptr<RenderQueue> RenderQueueRef;
	};
}