// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Brahmanda/Brahmanda.h"
#include "MyGame/Data/Block.h"

//...

class Highlighter : public Block
{
public:

	Highlighter(brm::EntityInitializer InInitializer)
		: Block(InInitializer) {}

	void Construct(const brm::ObjectTransform& InTransform) override;
	void Cycle(float DeltaTime);

	void UpdateLocation(float InX, float InY);
};