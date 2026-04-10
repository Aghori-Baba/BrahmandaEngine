// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/Mandala.h"
#include "Engine/GameFramework/WorldLayerCollection.h"

//...

class MyMandala : public Brahmanda::Mandala
{
public:

	MyMandala();
	virtual ~MyMandala() override;

	void OnInit() override;
	void PostInit() override;
	void OnCycle(float DeltaTime) override;
	void OnShutdown() override;

private:

	Brahmanda::WorldLayerCollection<8> WorldLayers;
};