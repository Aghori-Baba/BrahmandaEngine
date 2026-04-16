// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "MyGame.h"
#include "Engine/Core/Types/HandleTypes.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Core/Types/RenderableTypes.h"
#include "MyMandala.h"

//...

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::OnInit()
{
	ManagerRef = GetAssetManager();

}

void MyGame::OnCycle(float DeltaTime)
{
#pragma region ImGui

	//Enabling docking with main window
	ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
	ImGui::DockSpaceOverViewport(0U, ImGui::GetMainViewport());
	ImGui::PopStyleColor(2);

	ImGui::Begin("Brahmanda Test");

	ImGui::Text("Hello from ImGui Brahmanda");

	if (ImGui::Button("Interact"))
	{
		spdlog::info("Interaction Success!");
	}

	ImGui::End();

	ImGui::Begin("Brahmanda Options");

	ImGui::Text("This is options window");
	ImGui::Separator();
	ImGui::NewLine();
	float FPS = 1.f / DeltaTime;
	ImGui::Text("FPS: %.2f s (%.2f ms)", FPS, DeltaTime * 1000.f);

	ImGui::End();

#pragma endregion
}

void MyGame::OnShutdown()
{

}

std::unique_ptr<Brahmanda::Mandala> MyGame::ConstructMandala()
{
	return std::make_unique<MyMandala>();
}
