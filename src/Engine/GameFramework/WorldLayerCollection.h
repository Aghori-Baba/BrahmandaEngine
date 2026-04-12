// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <array>
#include <memory>
#include <type_traits>
#include <cassert>

#include "LayerContextData.h"


//...

namespace Brahmanda
{
	class WorldLayer;
	class AssetManager;

	enum class ELayerCollectionType
	{
		ELCT_NONE = 0,
		ELCT_Interior,
		ELCT_Exterior,
		ELCT_LightsOnly,
	};

	template <size_t N>
	struct WorldLayerCollection
	{
	public:

		WorldLayerCollection()
		{
			for (int i = 0; i < N; i++)
			{
				UsedIndices[i] = -1;
			}
		}

		~WorldLayerCollection() = default;

		WorldLayer* GetLayerAt(size_t InIndex)
		{
			assert(InIndex < MaxSize);
			return WorldLayerList[InIndex].get();
		}

		const WorldLayer* GetLayerAtConst(size_t InIndex) const
		{
			assert(InIndex < MaxSize);
			return WorldLayerList[InIndex].get();
		}

		std::array<std::unique_ptr<WorldLayer>, N>& GetLayerList()
		{
			return WorldLayerList;
		}

		const std::array<std::unique_ptr<WorldLayer>, N>& GetLayerListConst() const
		{
			return WorldLayerList;
		}

		template<typename T, typename... Args>
		T* CreateNewMap(LayerContextData& InData, Args... InArgs)
		{
			static_assert(std::is_base_of_v<Brahmanda::WorldLayer, T>, "T must derive from WorldLayer");

			if (ActiveSize >= MaxSize - 1)
			{
				Logger::Error("Cannot add more Layers. World List already full");

				return nullptr;
			}

			std::uint32_t _index = ActiveSize++;
			WorldLayerList[_index] = std::make_unique<T>(InData, std::forward<Args>(InArgs)...);
			_ptr->Construct();

			return WorldLayerList[_index].get();
		}

		template<typename T, typename... Args>
		T& AddLayerAt(size_t InIndex, LayerContextData& InData, Args... InArgs)
		{
			static_assert(std::is_base_of_v<Brahmanda::WorldLayer, T>, "T must derive from WorldLayer");
			assert(InIndex < MaxSize);
			assert(!WorldLayerList[InIndex] && "Layer already exists at Index");

			std::unique_ptr<T> _ptr = std::make_unique<T>(InData, std::forward<Args>(InArgs)...);
			_ptr->Construct();
			T& _ref = *_ptr;

			LoadedLayerList[InIndex] = _ptr.get();
			WorldLayerList[InIndex] = std::move(_ptr);
			ActiveSize++;

			return _ref;
		}

		template<typename T, typename... Args>
		T& SetLayerAt(size_t InIndex, LayerContextData& InData, Args... InArgs)
		{
			static_assert(std::is_base_of_v<Brahmanda::WorldLayer, T>, "T must derive from WorldLayer");
			assert(InIndex < MaxSize);

			std::unique_ptr<T> _ptr = std::make_unique<T>(InData, std::forward<Args>(InArgs)...);
			_ptr->Construct();
			T& _ref = *_ptr;
			LoadedLayerList[InIndex] = _ptr.get();
			WorldLayerList[InIndex] = std::move(_ptr);

			return _ref;
		}

		void RemoveLayerAt(size_t InIndex)
		{
			assert(InIndex < MaxSize);

			if (WorldLayerList[InIndex])
			{
				WorldLayerList[InIndex]->Unload();
				WorldLayerList[InIndex].reset();
				ActiveSize--;
			}
		}

		ELayerCollectionType GetLayerCollectionType() const
		{
			return CollectionType;
		}

		void SetLayerCollectionType(ELayerCollectionType InType)
		{
			CollectionType = InType;
		}

	private:

		size_t MaxSize = N;
		size_t ActiveSize = 0u;

		std::array<std::int32_t, N> UsedIndices;
		std::array<std::unique_ptr<WorldLayer>, N> WorldLayerList;
		std::array<WorldLayer*, N> LoadedLayerList;
		ELayerCollectionType CollectionType = ELayerCollectionType::ELCT_NONE;
	};
}