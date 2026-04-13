// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>

#include "Engine/Core/Types/HandleTypes.h"

struct Texture;
struct Geometry;
struct Model;

namespace Brahmanda
{
	class AssetManager : public IAssetBridge
	{
	public:

		AssetManager();
		~AssetManager();

		void Init();
		void Shutdown();

		TextureHandle ReqLoadTexture(const std::string& InPath);
		void AddTextureRef(uint32_t InID);
		void ReqUnloadTexture(const TextureHandle& InHandle);
		void ReleaseTexture(uint32_t InID);

		GeometryHandle ReqLoadGeometry(const std::string& InPath);
		void ReqUnloadGeometry(const GeometryHandle& InHandle);
		//void AssignTextureToGeo(const GeometryHandl& InHandle, const TextureHandle& InHandle); 

		void UnloadUnused();

		Texture& GetTexture(const TextureHandle& InHandle);
		Model* GetGeometry(const GeometryHandle& InHandle);

		//Interface Implementation
		void AddAssetRef(uint32_t InID, EAssetType InType) override;
		void ReqUnloadAsset(uint32_t InID, EAssetType InType) override;
		bool GetIsShuttingDown() const override;

	private:

		uint32_t LastTexID = 0u;
		uint32_t LastGeoID = 0u;
		bool bIsShuttingDown = false;
		std::unique_ptr<Texture> ErrorTexture;

		struct TextureEntry
		{
			std::unique_ptr<Texture> Data;
			uint32_t RefCount = 0u;
			std::string PathToAsset = "";
		};

		struct GeometryEntry
		{
			//std::unique_ptr<Geometry> Data;
			uint32_t RefCount = 0u;
			std::string PathToAsset = "";
		};

		std::unordered_map<uint32_t, TextureEntry> LoadedTextureList;
		std::unordered_map<std::string, uint32_t> LoadedTextureIDs;

		std::unordered_map<uint32_t, GeometryEntry> LoadedGeometryList;
		std::unordered_map<std::string, uint32_t> LoadedGeometryIDs;
	};
}