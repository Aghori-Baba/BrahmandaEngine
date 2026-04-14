// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "AssetManager.h"

#include <raylib.h>
#include "Engine/Systems/Logger.h"

//...

namespace Brahmanda
{
	AssetManager::AssetManager()
	{

	}

	AssetManager::~AssetManager()
	{
		bIsShuttingDown = true;
	}

	void AssetManager::Init()
	{
		ErrorTexture = std::make_unique<Texture>(LoadTexture(RESOURCE_DIR "t_error.png"));
	}

	TextureHandle AssetManager::RequestLoadTexture(const std::string& InPath)
	{
		auto It = LoadedTextureIDs.find(InPath);
		if (It != LoadedTextureIDs.end())
		{
			LoadedTextureList[It->second].RefCount += 1;
			Logger::Info("Loaded Texture found. TexId: {}, Ref count: {}", It->second, LoadedTextureList[It->second].RefCount);
			return TextureHandle(It->second, this);
		}

		uint32_t _id = ++LastTexID;
		LoadedTextureIDs[InPath] = _id;

		TextureEntry NewEntry;
		NewEntry.Data = std::make_unique<Texture>(LoadTexture(InPath.c_str()));
		NewEntry.RefCount += 1;
		NewEntry.PathToAsset = InPath;
		LoadedTextureList[_id] = std::move(NewEntry);
		//Logger::Info("New texture loaded.TexID: {}, Ref count: {}", _id, LoadedTextureList[TexID].RefCount);

		return TextureHandle(_id, this);
	}

	void AssetManager::AddTextureRef(uint32_t InID)
	{
		auto It = LoadedTextureList.find(InID);
		if (It == LoadedTextureList.end())
		{
			return;
		}

		It->second.RefCount++;
	}

	void AssetManager::ReqUnloadTexture(const TextureHandle& InHandle)
	{
		//Potentially Dead code. Prefer not to call this function manually.
		Logger::Warn("AssetManager - ReqUnloadTexture: Prefer not calling this function manually.");

		if (!InHandle.GetIsValid())
		{
			Logger::Info("Invalid Texture handle.");

			return;
		}

		uint32_t _id = InHandle.GetID();

		auto It = LoadedTextureList.find(_id);
		if (It == LoadedTextureList.end())
		{
			return;
		}

		if (It->second.RefCount == 0)
		{
			Logger::Info("Double delete detected!");

			return;
		}

		It->second.RefCount--;

		//Logger::Info("Released Texture handle. TexId: {}, Ref count: {}", ID, It->second.RefCount);

		if (It->second.RefCount == 0)
		{
			std::string& _path = It->second.PathToAsset;
			Texture* _tex = It->second.Data.get();

			//Logger::Info("Unloaded Texture. TexId: {}, Ref count: {}", ID, It->second.RefCount);

			UnloadTexture(*_tex);
			LoadedTextureIDs.erase(_path);
			LoadedTextureList.erase(It);
		}
	}

	void AssetManager::ReleaseTexture(uint32_t InID)
	{
		auto It = LoadedTextureList.find(InID);
		if (It == LoadedTextureList.end())
		{
			return;
		}

		if (It->second.RefCount == 0)
		{
			Logger::Warn("Double delete detected!");

			return;
		}

		It->second.RefCount--;

		//Logger::Info("Released a Texture handle. TexId: {}, Ref count: {}", InID, It->second.RefCount);

		if (It->second.RefCount == 0)
		{
			auto _path = It->second.PathToAsset;
			Texture* _tex = It->second.Data.get();

			//Logger::Info("Unloaded a Texture. TexId: {}, Ref count: {}", InID, It->second.RefCount);

			UnloadTexture(*_tex);
			LoadedTextureIDs.erase(_path);
			LoadedTextureList.erase(It);
		}
	}

	GeometryHandle AssetManager::RequestLoadGeometry(const std::string& InPath)
	{

		return GeometryHandle();
	}

	void AssetManager::RequestUnloadGeometry(const GeometryHandle& InHandle)
	{

	}

	void AssetManager::UnloadUnused()
	{

	}

	Texture& AssetManager::GetTexture(const TextureHandle& InHandle)
	{
		if (!InHandle.GetIsValid()) 
		{
			return *ErrorTexture;
		}

		auto It = LoadedTextureList.find(InHandle.GetID());
		if (It != LoadedTextureList.end())
		{
			Texture* _tex = It->second.Data.get();
			if (_tex)
			{
				return *_tex;
			}
		}

		return *ErrorTexture;
	}

	Model* AssetManager::GetGeometry(const GeometryHandle& InHandle)
	{

		return nullptr;
	}

	void AssetManager::AddAssetRef(uint32_t InID, EAssetType InType)
	{
		switch (InType)
		{
		case Brahmanda::EAssetType::EAT_NONE:

			break;

		case Brahmanda::EAssetType::EAT_Texture:

			AddTextureRef(InID);

			break;

		case Brahmanda::EAssetType::EAT_Geometry:

			break;

		case Brahmanda::EAssetType::EAT_SkeletalGeo:

			break;

		case Brahmanda::EAssetType::EAT_AudioFile:

			break;

		default:

			break;
		}
	}

	void AssetManager::RequestUnloadAsset(uint32_t InID, EAssetType InType)
	{
		switch (InType)
		{
		case Brahmanda::EAssetType::EAT_NONE:

			break;

		case Brahmanda::EAssetType::EAT_Texture:

			ReleaseTexture(InID);

			break;

		case Brahmanda::EAssetType::EAT_Geometry:

			break;

		case Brahmanda::EAssetType::EAT_SkeletalGeo:

			break;

		case Brahmanda::EAssetType::EAT_AudioFile:

			break;

		default:

			break;
		}
	}

	bool AssetManager::GetIsShuttingDown() const
	{
		return bIsShuttingDown;
	}

	void AssetManager::Shutdown()
	{
		bIsShuttingDown = true;
	}
}