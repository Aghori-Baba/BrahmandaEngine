// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Renderer.h"

#include <algorithm>

#include "ModuleIncludes.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/GameFramework/Scene/Camera.h"

//...

namespace Brahmanda
{
	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Brahmanda::Renderer::InitRenderer(AssetManager* InRef)
	{
		AssetManagerRef = InRef;
		
	}

	void Brahmanda::Renderer::ShutdownRenderer()
	{

	}

	void Brahmanda::Renderer::BeginRenderFrame()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		rlImGuiBegin();
	}

	void Renderer::RenderFrame(const FrameContextData& InContext)
	{
		auto* Cam = InContext.ActiveCamera;
		bool bIsOrtho = false;
		bool bHasActiveCam = Cam != nullptr;

		if (bHasActiveCam)
		{
			Cam->SetOffset({ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f });
			bIsOrtho = Cam->GetCameraType() == ORTHOGRAPHIC_CAM;

			if (bIsOrtho)
			{
				BeginMode2D(*(Cam->Get2DCamera()));
			}
			else
			{
				//TODO: 3D Mode not supported yet.
				//BeginMode3D(*(Cam->Get3DCamera()));
			}
		}

		auto& _items = InContext.PrimaryQueue.GetRenderItems();
		std::sort(_items.begin(), _items.end(), [](const RenderData& a, const RenderData& b) {return a.Tex.GetID() < b.Tex.GetID(); });
		auto& _texList = AssetManagerRef->GetLoadedTextureList(); //HACK: Dangerous array use. Not protected against deletion.
		TextureHandle _current = {};
		Texture* _t = &_texList[0];
		for (auto& It : _items)
		{
			if (_current.GetID() != It.Tex.GetID())
			{
				_current = It.Tex;
				_t = &_texList[It.Tex.GetID()];
			}
			const ObjectTransform& Transform = It.Transform;
			DrawTexturePro(*_t, { 0, 0, (float)_t->width, (float)_t->height }, { Transform.Pos[0], Transform.Pos[1], 100, 100 }, { 0, 0 }, Transform.Rot[0], WHITE);
		}

		if (bHasActiveCam)
		{
			if (bIsOrtho)
			{
				EndMode2D();
			}
			else
			{
				//TODO: 3D Mode not supported yet.
				//EndMode3D();
			}
		}
	}

	void Brahmanda::Renderer::EndRenderFrame()
	{
		rlImGuiEnd();

		EndDrawing();
	}
}

//auto& _items = InContext.PrimaryQueue.GetRenderItems();
//std::sort(_items.begin(), _items.end(), [](const RenderData& a, const RenderData& b) {return a.Tex.GetID() < b.Tex.GetID(); });
//auto& _texList = AssetManagerRef->GetLoadedTextureList(); //HACK: Dangerous array use. Not protected against deletion.
//TextureHandle _current = {};
//Texture* _t = &_texList[0];
//for (auto& It : _items)
//{
//	if (_current.GetID() != It.Tex.GetID())
//	{
//		_current = It.Tex;
//		_t = &_texList[It.Tex.GetID()];
//	}
//	const ObjectTransform& Transform = It.Transform;
//	DrawTexturePro(*_t, { 0, 0, (float)_t->width, (float)_t->height }, { Transform.Pos[0], Transform.Pos[1], 100, 100 }, { 0, 0 }, Transform.Rot[0], WHITE);
//}

//auto& _items = InContext.PrimaryQueue.GetRenderItems();
//std::sort(_items.begin(), _items.end(), [](const RenderData& a, const RenderData& b) { return a.Tex.GetID() < b.Tex.GetID(); });
//TextureHandle _current = {};
//Texture& _t = AssetManagerRef->GetTexture(_current);
//for (auto& It : _items)
//{
//	if (_current.GetID() != It.Tex.GetID())
//	{
//		_current = It.Tex;
//		_t = AssetManagerRef->GetTexture(It.Tex);
//	}
//	const ObjectTransform& Transform = It.Transform;
//	DrawTexturePro(_t, { 0, 0, (float)_t.width, (float)_t.height }, { Transform.Pos[0], Transform.Pos[1], 100, 100 }, {0, 0}, Transform.Rot[0], WHITE);
//}

//for (const auto& Item : InContext.PrimaryQueue.GetRenderItems())
//{
//	Texture& _t = AssetManagerRef->GetTexture(Item.Tex);
//	const ObjectTransform& Transform = Item.Transform;
//	DrawTexture(_t, Transform.Pos[0], Transform.Pos[1], WHITE);
//	DrawTexturePro(_t, { 0, 0, (float)_t.width, (float)_t.height }, { Transform.Pos[0], Transform.Pos[1], 100, 100 }, {0, 0}, Transform.Rot[0], WHITE);
//}