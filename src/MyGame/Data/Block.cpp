// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Block.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/Systems/Logger.h"

//...

Block::~Block()
{

}

void Block::Construct(const brm::ObjectTransform& InTransform)
{
	PARENT::Construct(InTransform);

	SpriteComp = CreateSubobject<brm::Sprite2D>();

	//Logger::Info("TEST INFO: {}, {}, {}", TransformComp->Pos[0], TransformComp->Rot[1], TransformComp->Scale[2]);
}

void Block::InitBlock()
{

}