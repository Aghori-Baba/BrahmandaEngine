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
	Create(100, 100);

	EntityMgr.GetContainerByType<brm::ObjectTransform>()->ReserveSize(100000u);

	Brahmanda::ObjectTransform Transform;
	Transform.Pos[0] = 0.f;
	Transform.Pos[1] = 0.f;
	MyPlayer* Player = SpawnEntity<MyPlayer>(Transform);
	auto& _playerSprite = Player->GetComponentHandleByClass<brm::Sprite2D>();
	if (_playerSprite.IsValid())
	{
		brm::TextureHandle _t = AssetManagerRef->GetOrLoadTexture(RESOURCE_DIR "textures.png");
		_playerSprite.Get().SpriteTex = _t;
		_playerSprite.Get().UV = {32.f * 28.f, 0.f, 32.f, 32.f};
		_playerSprite.Get().SetSortKey(0u, 1u, _t.GetID(), Player->GetEntityHandle().ID);
	}
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
	Brahmanda::TextureHandle _ts;

	if (!AssetManagerRef->GetIsShuttingDown())
	{
		_t = AssetManagerRef->GetOrLoadTexture(RESOURCE_DIR "dirt.png");
		_t1 = AssetManagerRef->GetOrLoadTexture(RESOURCE_DIR "frame.png");
		_t2 = AssetManagerRef->GetOrLoadTexture(RESOURCE_DIR "t_error.png");
		_ts = AssetManagerRef->GetOrLoadTexture(RESOURCE_DIR "textures.png");
	}

	int _i = 0;
	const float _cellSize = 32.f;
	for (Block*& It : MapData)
	{
		Brahmanda::ObjectTransform Transform;
		Transform.Pos[0] = 0.f + 1.f * (_i % InW);
		Transform.Pos[1] = 0.f + 1.f * (_i / InH);
		Transform.Rot[0] = 0.f;

 		It = SpawnEntity<Block>(Transform);
		It->Type = Block::air;
		if (_i % 2 == 0)
		{
			if (_i % 3 == 0)
			{
				It->Type = Block::leaves;
				It->SpriteComp.Get().SpriteTex = _ts;
				It->SpriteComp.Get().UV = { _cellSize * (float)It->Type, 0.f, _cellSize, _cellSize };
			}
			else
			{
				It->Type = Block::glass;
				It->SpriteComp.Get().SpriteTex = _ts;
				It->SpriteComp.Get().UV = { _cellSize * (float)It->Type, 0.f, _cellSize, _cellSize };
			}
		}
		else
		{
			It->Type = Block::bricks;
			It->SpriteComp.Get().SpriteTex = _ts;
			It->SpriteComp.Get().UV = { _cellSize * (float)It->Type, 0.f, _cellSize, _cellSize };
		}

		It->SpriteComp.Get().SetSortKey(2u, 1u, _ts.GetID(), It->GetEntityHandle().ID);

		_i++;
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
