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

		TextureHandle GetOrLoadTexture(const std::string& InPath);
		void AddTextureRef(uint32_t InID);
		void ReqUnloadTexture(const TextureHandle& InHandle);
		void ReleaseTexture(uint32_t InID);

		GeometryHandle RequestLoadGeometry(const std::string& InPath);
		void RequestUnloadGeometry(const GeometryHandle& InHandle);
		//void AssignTextureToGeo(const GeometryHandl& InHandle, const TextureHandle& InHandle); 

		void UnloadUnused();

		std::vector<Texture>& GetLoadedTextureList();
		Texture& GetTexture(const TextureHandle& InHandle);
		Model* GetGeometry(const GeometryHandle& InHandle);

		//Interface Implementation
		void AddAssetRef(uint32_t InID, EAssetType InType) override;
		void RequestUnloadAsset(uint32_t InID, EAssetType InType) override;
		uint32_t GetGenerationFromID(uint32_t InID, EAssetType InType) const override;
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
		std::vector<Texture> LoadedTextureData;
		std::vector<uint32_t> TextureFreelist;
		std::vector<uint32_t> TextureGenerations;

		std::unordered_map<uint32_t, GeometryEntry> LoadedGeometryList;
		std::unordered_map<std::string, uint32_t> LoadedGeometryIDs;
	};
}