// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Application.h"

#include "ModuleIncludes.h"
#include "Engine.h"

//...

namespace Brahmanda
{
	Application::Application()
	{

	}

	bool Application::InitApplication()
	{
#if PRODUCTION_BUILD == 1
		SetTraceLogLevel(LOG_NONE);
#endif

		std::string Title = std::string(Config::Engine::NAME) + std::string("-") + std::string(Config::Engine::VERSION);
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		InitWindow(1600, 900, Title.c_str());
		SetTargetFPS(240);

		rlImGuiSetup(true);

		ImGuiIO& IO = ImGui::GetIO();
		IO.FontGlobalScale = 1.25;
		IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsClassic();

		EngineRef = std::make_unique<Engine>();
		
		assert(GameRef && "Valid Game reference is required before Engine is initialized!");
		EngineRef->SetGame(GameRef);

		if (!EngineRef->InitEngine())
		{
			return false;
		}

		return true;
	}

	void Application::StartApplicationCycle()
	{
		assert(EngineRef && "Engine should be Initialized before executing the Game Loop!");
		while (!WindowShouldClose())
		{
			DeltaTime = GetFrameTime();
			EngineRef->CycleEngine(DeltaTime);
		}
	}

	void Application::ShutdownApplication()
	{
		EngineRef->ShutdownEngine();

		rlImGuiShutdown();
		CloseWindow();
	}

	void Application::Cleanup()
	{

	}

	void Application::ManageGame(IGame* InGame)
	{
		GameRef = InGame;
	}

	Application::~Application()
	{

	}
}