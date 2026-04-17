// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include "Engine/Brahmanda/Brahmanda.h"
#include "Engine/GameFramework/Scene/WorldEntity.h"

//...

class Block : public brm::WorldEntity
{
public:

	Block(brm::EntityInitializer InInitializer)
		: brm::WorldEntity(InInitializer) {}

	enum
	{
		air = 0,
		dirt,
		grassBlock,
		stone,
		grass,
		sand,
		sandRuby,
		sandStone,
		woodPlank,
		stoneBricks,
		clay,
		woodLog,
		leaves,
		copper,
		iron,
		gold,
		copperBlock,
		ironBlock,
		goldBlock,
		bricks,
		snow,
		ice,
		rubyBlock,
		platform,
		workBench,
		glass,
		furnace,
		painting,
		sappling,
		snowBlueRuby,
		blueRubyBlock,
		door,
		jar,
		table,
		wordrobe,
		bookShelf,
		snowBricks,
		iceTable,
		iceWordrobe,
		iceBookShelf,
		icePlatform,
		sandTable,
		sandWordrobe,
		sandBookShelf,
		sandPlatform,
		woodenChest,
		iceChest,
		sandChest,
		boneChest,
		boneBricks,
		boneBench,
		boneWordrobe,
		boneBookShelf,
		bonePlatform,

		BLOCKS_COUNT,
	};

	~Block();

	void Construct(const brm::ObjectTransform& InTransform) override;

	void InitBlock();

	uint16_t Type = 0;

	brm::ComponentHandle<brm::Sprite2D> SpriteComp;
};