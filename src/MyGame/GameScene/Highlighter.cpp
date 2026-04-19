// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Highlighter.h"


//...

void Highlighter::Construct(const brm::ObjectTransform& InTransform)
{
	Block::Construct(InTransform);


}

void Highlighter::Cycle(float DeltaTime)
{
	//brm::Vector2 WorldPos = GetScreenToWorld2D(GetMousePosition(), CameraMana);
}

void Highlighter::UpdateLocation(float InX, float InY)
{
	TransformComp.Get().Pos[0] = (int)floor(InX);
	TransformComp.Get().Pos[1] = (int)floor(InY);
}
