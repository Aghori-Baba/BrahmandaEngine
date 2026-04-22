// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "Renderer.h"

#include <algorithm>

#include "ModuleIncludes.h"
#include "Engine/Core/Types/AssetTypes.h"
#include "Engine/Systems/Logger.h"
#include "Engine/Systems/AssetManager.h"
#include "Engine/GameFramework/Scene/Camera.h"
#include "Engine/GameFramework/SceneProxy.h"

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
		ClearBackground({ 80, 180, 255, 255 });

		rlImGuiBegin();
	}

	void Renderer::RenderPass2D(GameCamera* InCam, const SceneProxy2D* InSceneProxy)
	{
		bool bIsOrtho = false;

		if (InCam)
		{
			InCam->SetOffset({ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f });
			bIsOrtho = InCam->GetCameraType() == ORTHOGRAPHIC_CAM;

			if (bIsOrtho)
			{
				BeginMode2D(*(InCam->Get2DCamera()));
			}
		}

		auto& _itemsList = InSceneProxy->GetProxyData();
		auto& _texList = AssetManagerRef->GetLoadedTextureList();
		TextureHandle _current = {};
		Texture* _t = &_texList[0];
		Vector4 _uv = {};
		for (auto& _items : _itemsList)
		{
			for (auto& _item : _items)
			{
				uint32_t _id = _item.tex.GetID();
				if (_current.GetID() != _id)
				{
					_current = _item.tex;
					_t = &_texList[_id];
				}
				_uv = _item.uv;
				DrawTexturePro(*_t, { _uv.X, _uv.Y, _uv.Z, _uv.W }, { _item.x, _item.y, _item.sx, _item.sy }, { 0, 0 }, _item.r, WHITE);
			}
		}

		if (bIsOrtho)
		{
			EndMode2D();
		}
	}

	void Renderer::RenderPass3D(GameCamera* InCam, const SceneProxy* InSceneProxy)
	{

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

		//auto& items = InContext.PrimaryQueue.GetRenderItems();
		//auto& texList = AssetManagerRef->GetLoadedTextureList();

		//uint32_t currentID = UINT32_MAX;
		//Texture* t = &texList[0];
		//Rectangle src;

		//for (auto& It : items)
		//{
		//	uint32_t texID = It.Tex.GetID();

		//	if (currentID != texID)
		//	{
		//		currentID = texID;
		//		t = &texList[texID];
		//		src = { 0, 0, (float)t->width, (float)t->height };
		//	}

		//	const ObjectTransform& tr = *It.Transform;

		//	Rectangle dest;
		//	dest.x = tr.Pos[0];
		//	dest.y = tr.Pos[1];
		//	dest.width = tr.Scale[0];
		//	dest.height = tr.Scale[1];

		//	DrawTexturePro(*t, src, dest, { 0, 0 }, tr.Rot[0], WHITE);
		//}

		//auto& _items = InContext.PrimaryQueue.GetRenderItems();
		//auto& _texList = AssetManagerRef->GetLoadedTextureList(); //HACK: Dangerous array use. Not protected against deletion.
		//TextureHandle _current = {};
		//uint32_t _cid = _current.GetID();
		//Texture* _t = &_texList[0];
		//for (auto& It : _items)
		//{
		//	uint32_t _id = It.Tex.GetID();
		//	if (_cid != _id)
		//	{
		//		_current = It.Tex;
		//		_cid = _id;
		//		_t = &_texList[_id];
		//	}
		//	const ObjectTransform& Transform = *It.Transform;
		//	DrawTexturePro(*_t, { 0, 0, (float)_t->width, (float)_t->height }, { Transform.Pos[0], Transform.Pos[1], Transform.Scale[0], Transform.Scale[1] }, { 0, 0 }, Transform.Rot[0], WHITE);
		//}