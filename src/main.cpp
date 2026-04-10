// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Engine/Core/Application.h"
#include "MyGame/GameSystems/MyGame.h"

//...

int main()
{
	Brahmanda::Application App;
	MyGame NewGame;

	App.ManageGame(&NewGame);
	if (App.InitApplication())
	{
		App.StartApplicationCycle();
	}

	App.ShutdownApplication();

	return 0;
}