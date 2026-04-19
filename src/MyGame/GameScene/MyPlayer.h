// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Brahmanda/Brahmanda.h"
#include "Engine/GameFramework/Scene/Pawn.h"

//...

namespace Brahmanda
{
	class InputManager;
	class GameCamera;
}

class Highlighter;

class MyPlayer : public brm::Pawn
{
public:

	MyPlayer(brm::EntityInitializer InInitializer)
		: Pawn(InInitializer) {}

	~MyPlayer();

	void Construct(const brm::ObjectTransform& InTransform) override;
	void Cycle(float DeltaTime) override;
	void SetupInput(brm::InputManager* InputMgr) override;

public:

	Highlighter* HighlighterRef = nullptr;

protected:

	brm::ComponentHandle<brm::Sprite2D> SpriteTex;
	brm::GameCamera* GameCam = nullptr;

};