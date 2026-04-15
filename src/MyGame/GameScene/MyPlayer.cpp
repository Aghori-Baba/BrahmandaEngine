// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "MyPlayer.h"
#include "Engine/Systems/Logger.h"

//...


MyPlayer::~MyPlayer()
{

}

void MyPlayer::Construct(const brm::ObjectTransform& InTransform)
{
	PARENT::Construct(InTransform);

	SpriteTex = CreateSubobject<brm::TextureHandle>();
}

void MyPlayer::SetupInput(brm::InputManager* InputMgr)
{
	Logger::Info("Possessed MyPlayer!");
}
