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
		virtual void ReqUnloadAsset(uint32_t InID, EAssetType InType) = 0;
		virtual bool GetIsShuttingDown() const = 0;
	};

	struct AssetHandle
	{
		AssetHandle() = default;

		AssetHandle(uint32_t InID, EAssetType InType, IAssetBridge* InMgrRef)
			: AssetID(InID), bIsVisible(true), AssetType(InType), ManagerRef(InMgrRef)
		{

		}

		AssetHandle(const AssetHandle& Other)
		{
			AssetID = Other.AssetID;
			bIsVisible = Other.bIsVisible;
			AssetType = Other.AssetType;
			ManagerRef = Other.ManagerRef;

			AddRef();
		}

		AssetHandle(AssetHandle&& Other) noexcept
		{
			AssetID = Other.AssetID;
			bIsVisible = Other.bIsVisible;
			AssetType = Other.AssetType;
			ManagerRef = Other.ManagerRef;

			Other.AssetID = 0u;
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
			bIsVisible = Other.bIsVisible;
			AssetType = Other.AssetType;
			ManagerRef = Other.ManagerRef;

			AddRef();

			return *this;
		}

		void ReleaseHandle()
		{
			Release();

			AssetID = 0u;
			bIsVisible = false;
			AssetType = EAssetType::EAT_NONE;
			ManagerRef = nullptr;
		}

		uint32_t GetID() const
		{
			return AssetID;
		}

		uint32_t GetIsValid() const
		{
			return AssetID != 0u && ManagerRef != nullptr;
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
					ManagerRef->ReqUnloadAsset(AssetID, AssetType);
				}
			}

			AssetID = 0u;
			bIsVisible = false;
			AssetType = EAssetType::EAT_NONE;
			ManagerRef = nullptr;
		}

	private:

		uint32_t AssetID = 0u;
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

		TextureHandle(uint32_t InID, IAssetBridge* InMgrRef)
			: AssetHandle(InID, EAssetType::EAT_Texture, InMgrRef)
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

		GeometryHandle(uint32_t InID, IAssetBridge* InMgrRef)
			: AssetHandle(InID, EAssetType::EAT_Geometry, InMgrRef)
		{

		}

		//Additional Data
		//...
	};
}