// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "GameMap01.h"

#include "Engine/Systems/Logger.h"
#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/Systems/InputManager.h"

#include "MyGame/Data/Block.h"
#include "MyGame/Data/TestObject01.h"
#include "MyGame/GameScene/MyPlayer.h"

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
	Create(70, 70);

	Brahmanda::ObjectTransform Transform;
	Transform.Pos[0] = -100.f;
	Transform.Pos[1] = -100.f;
	MyPlayer* Player = SpawnEntity<MyPlayer>(Transform);
	Player->GetComponentHandleByClass<brm::TextureHandle>().Get() = AssetManagerRef->RequestLoadTexture(RESOURCE_DIR "dirt.png");
	RegisterForCycle(Player);
	InputMgr->PossessPawn(Player);

	RegisterRenderables();
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
	Brahmanda::TextureHandle _t1;
	Brahmanda::TextureHandle _t2;
	if (!AssetManagerRef->GetIsShuttingDown())
	{
		_t = AssetManagerRef->RequestLoadTexture(RESOURCE_DIR "dirt.png");
		_t1 = AssetManagerRef->RequestLoadTexture(RESOURCE_DIR "frame.png");
		_t2 = AssetManagerRef->RequestLoadTexture(RESOURCE_DIR "t_error.png");
	}

	int _i = 0;
	for (Block*& It : MapData)
	{
		Brahmanda::ObjectTransform Transform;
		Transform.Pos[0] = 0.f + 101 * (_i % 20);
		Transform.Pos[1] = 0.f + 101 * (_i / 20);
		Transform.Rot[0] = 0.f;

 		It = SpawnEntity<Block>(Transform);
		if (_i % 2 == 0)
		{
			if (_i % 3 == 0)
			{
				It->TextureComp.Get() = _t;
			}
			else
			{
				It->TextureComp.Get() = _t1;
			}

		}
		else
		{
			It->TextureComp.Get() = _t2;
		}

		_i++;
	}

	//RegisterRenderables();

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
