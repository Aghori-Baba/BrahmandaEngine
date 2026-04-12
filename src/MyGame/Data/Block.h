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

		BLOCKS_COUNT
	};

	~Block();

	void Construct(const brm::ObjectTransform& InTransform) override;

	void InitBlock();

	uint16_t Type = 0;

	brm::ComponentHandle<brm::TextureHandle> TextureComp;
};