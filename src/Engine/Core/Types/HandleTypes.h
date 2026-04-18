// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>

namespace Brahmanda
{
	enum class EAssetType
	{
		EAT_NONE,
		EAT_Texture,
		EAT_Geometry,
		EAT_SkeletalGeo,
		EAT_AudioFile,
	};

	class IAssetBridge
	{
	public:
		IAssetBridge() {};
		virtual ~IAssetBridge() {};

		virtual void AddAssetRef(uint32_t InID, EAssetType InType) = 0;
		virtual void RequestUnloadAsset(uint32_t InID, EAssetType InType) = 0;
		virtual uint32_t GetGenerationFromID(uint32_t InID, EAssetType InType) const = 0;
		virtual bool GetIsShuttingDown() const = 0;
	};

	struct AssetHandle
	{
		AssetHandle() = default;

		AssetHandle(uint32_t InID, uint32_t InGen, EAssetType InType, IAssetBridge* InMgrRef)
			: AssetID(InID), Generation(InGen), bIsVisible(true), AssetType(InType), ManagerRef(InMgrRef)
		{

		}

		AssetHandle(const AssetHandle& Other)
		{
			AssetID = Other.AssetID;
			Generation = Other.Generation;
			bIsVisible = Other.bIsVisible;
			AssetType = Other.AssetType;
			ManagerRef = Other.ManagerRef;

			AddRef();
		}

		AssetHandle(AssetHandle&& Other) noexcept
		{
			AssetID = Other.AssetID;
			Generation = Other.Generation;
			bIsVisible = Other.bIsVisible;
			AssetType = Other.AssetType;
			ManagerRef = Other.ManagerRef;

			Other.AssetID = UINT32_MAX;
			Other.Generation = UINT32_MAX;
			Other.bIsVisible = false;
			Other.AssetType = EAssetType::EAT_NONE;
			Other.ManagerRef = nullptr;
		}

		~AssetHandle()
		{
			Release();
		}

		AssetHandle& operator=(const AssetHandle& Other)
		{
			if (this == &Other)
			{
				return *this;
			}

			Release();

			AssetID = Other.AssetID;
			Generation = Other.Generation;
			bIsVisible = Other.bIsVisible;
			AssetType = Other.AssetType;
			ManagerRef = Other.ManagerRef;

			AddRef();

			return *this;
		}

		void ReleaseHandle()
		{
			Release();

			AssetID = UINT32_MAX;
			Generation = UINT32_MAX;
			bIsVisible = false;
			AssetType = EAssetType::EAT_NONE;
			ManagerRef = nullptr;
		}

		uint32_t GetID() const
		{
			return AssetID;
		}

		uint32_t IsValid() const
		{
			return AssetID != UINT32_MAX && 
				ManagerRef != nullptr && 
				ManagerRef->GetGenerationFromID(AssetID, AssetType) == Generation;
		}

		bool GetIsVisible() const
		{
			return bIsVisible;
		}

		void SetIsVisible(bool InNewState)
		{
			bIsVisible = InNewState;
		}

	private:

		void AddRef()
		{
			if (AssetID && ManagerRef)
			{
				ManagerRef->AddAssetRef(AssetID, AssetType);
			}
		}

		void Release()
		{
			if (AssetID && ManagerRef)
			{
				if (!ManagerRef->GetIsShuttingDown())
				{
					ManagerRef->RequestUnloadAsset(AssetID, AssetType);
				}
			}

			AssetID = UINT32_MAX;
			Generation = UINT32_MAX;
			bIsVisible = false;
			AssetType = EAssetType::EAT_NONE;
			ManagerRef = nullptr;
		}

	private:

		uint32_t AssetID = UINT32_MAX;
		uint32_t Generation = UINT32_MAX;
		bool bIsVisible = true;
		EAssetType AssetType = EAssetType::EAT_NONE;
		IAssetBridge* ManagerRef = nullptr;
	};

	struct TextureHandle : public AssetHandle
	{
		TextureHandle()
			: AssetHandle()
		{

		}

		TextureHandle(uint32_t InID, uint32_t InGen, IAssetBridge* InMgrRef)
			: AssetHandle(InID, InGen, EAssetType::EAT_Texture, InMgrRef)
		{

		}

		//Additional Data
		//...
	};

	struct GeometryHandle : public AssetHandle
	{
		GeometryHandle()
			: AssetHandle()
		{

		}

		GeometryHandle(uint32_t InID, uint32_t InGen, IAssetBridge* InMgrRef)
			: AssetHandle(InID, InGen, EAssetType::EAT_Geometry, InMgrRef)
		{

		}

		//Additional Data
		//...
	};
}