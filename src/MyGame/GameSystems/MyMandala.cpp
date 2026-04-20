// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "MyMandala.h"
#include "Engine/Systems/Logger.h"
#include "Engine/GameFramework/WorldLayer.h"
#include "Engine/GameFramework/LayerContextData.h"
#include "Engine/Core/Types/RenderableTypes.h"

#include "MyGame/Maps/GameMap01.h"

//...

MyMandala::MyMandala()
{

}

MyMandala::~MyMandala()
{

}

void MyMandala::OnInit()
{
	Logger::Info("MyMandala - Init - Called from Derived class");
}

void MyMandala::PostInit()
{
	//Brahmanda::LayerInitData LayerData;
	Brahmanda::WorldLayer& Map = Collection.AddLayerAt<GameMap01>(0, LayerData);
	Map.Load();

	GatherRenderables();
}

void MyMandala::OnCycle(float DeltaTime)
{

}

void MyMandala::OnShutdown()
{
	Logger::Info("MyMandala - Shutdown - Called from Derived class");

	//...
}
