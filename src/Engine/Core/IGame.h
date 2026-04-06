// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "CoreIncludes.h"

//...

namespace Brahmanda
{
	class AssetManager;
	class EntityManager;
	class Renderer;
	struct FrameContextData;

	struct GameInitalizerData
	{
		AssetManager* AssetMgr = nullptr;
		EntityManager* EntityMgr = nullptr;
	};

	class IGame
	{
	public:

		virtual ~IGame() = default;

		virtual void Construct(GameInitalizerData Initializer) = 0;
		virtual void Init() = 0;
		virtual void Cycle(float DeltaTime, FrameContextData& InContext) = 0;
		virtual void Shutdown() = 0;
	};
}