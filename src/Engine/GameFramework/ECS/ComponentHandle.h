// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <assert.h>
#include "Component.h"

//...

namespace Brahmanda
{
	struct Entity;
	class WorldLayer;

	template<typename T>
	class ComponentHandle
	{
	public:

		~ComponentHandle() {};

		ComponentHandle(Entity InOwner, ComponentContainer<T>* InContainer, WorldLayer* InWorld)
			: Owner(InOwner), Container(InContainer), OwningWorld(InWorld)
		{

		}

		ComponentHandle() = default;
		ComponentHandle(const ComponentHandle& Other) = default;
		ComponentHandle& operator=(const ComponentHandle& Other) = default;
		ComponentHandle(ComponentHandle&& Other) = default;
		ComponentHandle& operator=(ComponentHandle&& Other) = default;

		bool IsValid() const
		{
			return Container && Container->HasComponent(Owner);
		}

		T& Get()
		{
			assert(Container->HasComponent(Owner) && "Owner does not have requested Component");
			return Container->GetComponent(Owner);
		}

		const T& Get() const
		{
			assert(Container->HasComponent(Owner) && "Owner does not have requested Component");
			return Container->GetComponent(Owner);
		}

		T* operator->()
		{
			return &Get();
		}

		const T* operator->() const
		{
			return &Get();
		}

		void RemoveComponent()
		{
			Container->DeleteComponent(Owner);
			Owner = {};
			Container = nullptr;
			OwningWorld = nullptr;
		}

		void RegisterHandle()
		{

		}

		void UnregisterHandle()
		{

		}

	private:

		Entity Owner = {};
		ComponentContainer<T>* Container = nullptr;
		WorldLayer* OwningWorld = nullptr;
	};
}