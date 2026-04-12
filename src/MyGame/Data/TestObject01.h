// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include "Engine/Brahmanda/Brahmanda.h"
#include "GameFramework/Scene/WorldEntity.h"

//...

class TestObject01 : public brm::WorldEntity
{
public:

	TestObject01(brm::EntityInitializer InInitializer)
		: PARENT(InInitializer) {}

	~TestObject01();

	void Construct(const brm::ObjectTransform& InTransform) override;

private:

};