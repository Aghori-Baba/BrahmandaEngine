// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include "Engine/GameFramework/ECS/Entity.h"

//...

class Block : public Brahmanda::Entity
{
public:

	enum
	{
		air = 0,
		dirt,

		BLOCKS_COUNT
	};

	Block(const Brahmanda::ObjectTransform& InTransform)
		: Entity(InTransform)
	{

	}

	~Block();

	void InitBlock();

	uint16_t Type = 0;
};