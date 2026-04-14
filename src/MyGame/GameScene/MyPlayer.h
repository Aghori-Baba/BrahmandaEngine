// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Brahmanda/Brahmanda.h"
#include "Engine/GameFramework/Scene/Pawn.h"

//...

namespace Brahmanda
{
	class InputManager;
}

class MyPlayer : public brm::Pawn
{
public:

	MyPlayer(brm::EntityInitializer InInitializer)
		: Pawn(InInitializer) {}

	~MyPlayer();

	void SetupInput(brm::InputManager* InputMgr) override;
};