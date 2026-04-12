// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "TestObject01.h"
#include "Core/Types/CustomTypes.h"
#include "Systems/Logger.h"
#include "GameFramework/ECS/ComponentHandle.h"

//...


void TestObject01::Construct(const brm::ObjectTransform& InTransform)
{
	PARENT::Construct(InTransform);

	brm::ComponentHandle<brm::ObjectTransform> Comp = CreateSubobject<Brahmanda::ObjectTransform>();
	Comp->Rot[1] = 45.f;
	Logger::Info("TEST INFO: {}, {}, {}", Comp->Pos[0], Comp->Rot[1], Comp->Scale[2]);
}

TestObject01::~TestObject01()
{

}