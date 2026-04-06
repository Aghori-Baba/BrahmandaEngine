// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "CoreIncludes.h"

namespace Brahmanda
{
	class Engine;
	class IGame;

	class Application
	{
	public:
		Application();
		~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		bool InitApplication();
		void StartApplicationCycle();
		void ShutdownApplication();

		void Cleanup();

		void ManageGame(IGame* InGame);

	private:

		std::unique_ptr<Engine> EngineRef = nullptr;
		IGame* GameRef = nullptr;
		float DeltaTime = 0.f;
	};
}