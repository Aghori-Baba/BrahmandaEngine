// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Game.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Core/Types/RenderableTypes.h"
#include "Mandala.h"

//...

namespace Brahmanda
{
	Game::Game()
	{

	}

	void Game::Init()
	{
		Logger::Info("Game Initialized!");

		MandalaRef = ConstructMandala();

		ManadalaInitializerData InitData;
		InitData.AssetMgr = AssetManagerRef;
		MandalaRef->Construct(InitData);
		MandalaRef->Init();

		OnInit();
	}

	void Game::Construct(GameInitalizerData Initilizer)
	{
		AssetManagerRef = Initilizer.AssetMgr;
	}

	void Game::OnInit()
	{

	}

	void Game::Cycle(float DeltaTime, FrameContextData& InContext)
	{
		OnCycle(DeltaTime);

		MandalaRef->Cycle(DeltaTime, InContext);
	}

	void Game::OnCycle(float DeltaTime)
	{

	}

	void Game::Shutdown()
	{
		OnShutdown();

		//...

		MandalaRef->Shutdown();
	}

	void Game::OnShutdown()
	{

	}

	AssetManager* Game::GetAssetManager() const
	{
		return AssetManagerRef;
	}

	std::unique_ptr<Mandala> Game::ConstructMandala()
	{
		return std::make_unique<Mandala>();
	}

	Mandala* Game::GetGameMandala() const
	{
		return MandalaRef.get();
	}

	Game::~Game()
	{

	}
}