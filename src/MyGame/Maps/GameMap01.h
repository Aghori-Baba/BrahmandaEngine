// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>

#include "Engine/GameFramework/WorldLayer.h"

//...

class Block;

class GameMap01 : public Brahmanda::WorldLayer
{
public:

	GameMap01(const Brahmanda::LayerContextData& InData);
	~GameMap01();

	void OnLoad() override;
	void OnUnload() override;

	void Create(int InW, int InH);
	Block& GetBlockUnsafe(int InX, int InY);
	Block* GetBlockSafe(int InX, int InY);

	int w = 0;
	int h = 0;

	std::vector<Block*> MapData;
};