// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "GameMap01.h"
#include "MyGame/Data/Block.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Core/Types/CustomTypes.h"

//...

GameMap01::GameMap01(const Brahmanda::LayerContextData& InData)
	: WorldLayer(InData)
{
	Logger::Info("GameMap01 Loaded!");
}

GameMap01::~GameMap01()
{

}

void GameMap01::OnLoad()
{
	Create(30, 10);
	GetBlockUnsafe(0, 0).Type = Block::dirt;
	GetBlockUnsafe(1, 1).Type = Block::dirt;
	GetBlockUnsafe(2, 2).Type = Block::dirt;
	GetBlockUnsafe(3, 3).Type = Block::dirt;
	GetBlockUnsafe(4, 4).Type = Block::dirt;
	GetBlockUnsafe(5, 5).Tex.ReleaseHandle();
}

void GameMap01::OnUnload()
{

}

void GameMap01::Create(int InW, int InH)
{
	MapData.resize(InW * InH);

	w = InW;
	h = InH;

	Brahmanda::TextureHandle _t;
	if (!AssetManagerRef->GetIsShuttingDown())
	{
		_t = AssetManagerRef->ReqLoadTexture(RESOURCE_DIR "dirt.png");
	}

	int i = 0;
	for (Block*& It : MapData)
	{
		Brahmanda::ObjectTransform Transform;
		Transform.Pos[0] = 0.f + 101 * (i % 20);
		Transform.Pos[1] = 0.f + 101 * (i / 20);
		Transform.Rot[0] = 15.f;

		It = SpawnEntity<Block>(Transform);
		It->Tex = _t;
		if (i % 2 == 0)
		{
			It->Tex.SetIsVisible(false);
		}
		RegisterEntity(*It);

		i++;
	}

	Logger::Info("GameMap01 - MapData Loaded!");
}

Block& GameMap01::GetBlockUnsafe(int InX, int InY)
{
	assert(MapData.size() == w * h && "MapData not Initialized!");
	assert(InX >= 0 || InY >= 0 || InX < w || InY < h && "GetBlockUnsafe Out of Bounds error!");

	return *MapData[InX + InY * w];
}

Block* GameMap01::GetBlockSafe(int InX, int InY)
{
	if (InX < 0 || InY < 0 || InX >= w || InY >= h)
	{
		return nullptr;
	}

	return MapData[InX + InY * w];
}
