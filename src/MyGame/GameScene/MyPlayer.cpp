// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "MyPlayer.h"

#include "raylib.h"

#include "Engine/Systems/Logger.h"
#include "Engine/GameFramework/Scene/Camera.h"
#include "Engine/Systems/CameraManager.h"

#include "MyGame/Maps/GameMap01.h"
#include "MyGame/GameScene/Highlighter.h"

//...


MyPlayer::~MyPlayer()
{

}

void MyPlayer::Construct(const brm::ObjectTransform& InTransform)
{
	PARENT::Construct(InTransform);

	SpriteTex = CreateSubobject<brm::Sprite2D>();
	PawnCamera.Get().SetCameraZoom(100.f);

	GameCam = OwningWorld->GetCameraManager()->GetPrimaryCamera();
}

void MyPlayer::Cycle(float DeltaTime)
{
	PARENT::Cycle(DeltaTime);

	if (HighlighterRef)
	{
		Vector2 WorldPos = GetScreenToWorld2D(GetMousePosition(), *GameCam->Get2DCamera());

		HighlighterRef->UpdateLocation(WorldPos.x, WorldPos.y);
	}
}

void MyPlayer::SetupInput(brm::InputManager* InputMgr)
{
	Logger::Info("Possessed MyPlayer!");
}
