// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/ECS/Entity.h"
#include "Engine/GameFramework/ECS/Component.h"
#include "Engine/GameFramework/ECS/ComponentHandle.h"
#include "Engine/GameFramework/Scene/WorldEntityInitializer.h"
#include "Engine/Systems/EntityManager.h"

//...

namespace Brahmanda
{
	class WorldCamera;

	class WorldEntity
	{
	public:

		using PARENT = WorldEntity;

		WorldEntity() = delete;

		WorldEntity(EntityInitializer InInitializer)
			: EntityHandle(InInitializer.EntityHandle), OwningWorld(InInitializer.OwningWorld), EntityMgr(InInitializer.EntityMgr)
		{

		}

		~WorldEntity();

		virtual void Construct(const ObjectTransform& InTransform);
		virtual void Init();
		virtual void Cycle(float DeltaTime);
		virtual void Shutdown();
		
		void RegisterForCycle();

		const bool GetCanCycle() const;
		const Entity GetEntityHandle() const;

		template<typename T>
		ComponentHandle<T> GetComponentHandleByClass() const
		{
			auto* _container = EntityMgr->GetContainerByType<T>();
			if (_container->HasComponent(EntityHandle))
			{
				T& _comp = _container->GetComponent(EntityHandle);
				return ComponentHandle<T>(EntityHandle, _container, OwningWorld);
			}

			return ComponentHandle<T>(Entity::InvalidEntity(), nullptr, nullptr);
		}

		void AttachChild(WorldEntity* InChild)
		{

		}

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

		ComponentHandle<ObjectTransform> TransformComp;

		Entity EntityHandle = {};
		WorldLayer* OwningWorld = nullptr;
		EntityManager* EntityMgr = nullptr;

	private:

		std::vector<WorldEntity*> Children;
	};
}