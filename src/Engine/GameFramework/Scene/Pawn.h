// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <memory>

#include "Engine/Core/Types/CustomTypes.h"
#include "Engine/GameFramework/ECS/Entity.h"

//...

namespace Brahmanda
{
	class WorldCamera;
	class InputManager;

	class Pawn : public Entity
	{
	public:

		Pawn() = default;
		~Pawn() = default;

		void Construct();
		void Init();
		void SetupInput(InputManager* InputMgr);

		std::unique_ptr<WorldCamera> PawnCam;
	};
}