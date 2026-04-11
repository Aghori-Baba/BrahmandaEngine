// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/ECS/Entity.h"
#include "Engine/GameFramework/ECS/Component.h"
#include "Engine/GameFramework/ECS/ComponentHandle.h"
#include "Engine/Systems/EntityManager.h"

//...

namespace Brahmanda
{
	struct EntityInitializer
	{
		Entity EntityHandle = {};
		WorldLayer* OwningWorld = nullptr;
		EntityManager* EntityMgr = nullptr;
	};

	class WorldEntity
	{
	public:

		WorldEntity() = delete;

		WorldEntity(EntityInitializer InInitializer)
			: EntityHandle(InInitializer.EntityHandle), OwningWorld(InInitializer.OwningWorld), EntityMgr(InInitializer.EntityMgr)
		{

		}

		~WorldEntity();

		virtual void Construct();
		virtual void Init();
		virtual void Cycle(float DeltaTime);
		virtual void Shutdown();

		const Entity GetEntityHandle() const;

	protected:

		template<typename T, typename... Args>
		[[nodiscard]] ComponentHandle<T> CreateSubobject(Args&&... InArgs)
		{
			auto* _container = EntityMgr->GetContainerByType<T>();
			T& _comp = _container->CreateNewComponent(EntityHandle, std::forward<Args>(InArgs)...);
			return ComponentHandle<T>(EntityHandle, _container, OwningWorld);
		}

	protected:

		bool bCanRunCycle = true;

		Entity EntityHandle = {};
		WorldLayer* OwningWorld = nullptr;
		EntityManager* EntityMgr = nullptr;

	private:

	};
}