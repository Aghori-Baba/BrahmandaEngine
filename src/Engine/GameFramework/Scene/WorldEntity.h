// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/GameFramework/ECS/Entity.h"
#include "Engine/GameFramework/ECS/Component.h"
#include "Engine/Systems/EntityManager.h"

//...

namespace Brahmanda
{
	class WorldEntity
	{
	public:

		WorldEntity();
		~WorldEntity();

		virtual void Construct();
		virtual void Init();
		virtual void Cycle(float DeltaTime);
		virtual void Shutdown();

	protected:

		template<typename T, typename... Args>
		T* CreateSubobject(Args&&... InArgs)
		{
			auto* _container = EntityMgr->GetContainerByType<T>();
			return &_container->CreateNewComponent(EntityHandle, std::forward<Args>(InArgs)...);
		}

	protected:

		bool bCanRunCycle = true;

		Entity EntityHandle = {};
		WorldLayer* OwningWorld = nullptr;
		EntityManager* EntityMgr = nullptr;

	private:

	};
}