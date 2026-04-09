// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <vector>
#include <cstdint>

//...

namespace Brahmanda
{
	class Entity;

	class EntityManager
	{
	public:

		EntityManager() = default;
		~EntityManager() = default;

		void Init();
		void Shutdown();

		Entity CreateNewEntity();
		void DestroyEntity(Entity InEntity);
		bool IsEntityAlive(Entity InEntity);

	private:

		std::vector<uint32_t> FreeList;
		std::vector<uint32_t> Generations;
	};
}