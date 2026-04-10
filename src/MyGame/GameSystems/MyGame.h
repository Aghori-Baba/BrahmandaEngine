// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/Game.h"

//...

namespace Brahmanda
{
	struct TextureHandle;
	class AssetManager;
	class Mandala;
	class FrameContextData;
}



class MyGame : public Brahmanda::Game
{
public:

	MyGame();
	~MyGame();

	void OnInit() override;
	void OnCycle(float DeltaTime) override;
	void OnShutdown() override;

	std::unique_ptr<Brahmanda::Mandala> ConstructMandala() override;

private:

	Brahmanda::AssetManager* ManagerRef = nullptr;
};