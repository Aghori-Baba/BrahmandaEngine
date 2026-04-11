// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#include "TestObject01.h"
#include "Core/Types/CustomTypes.h"
#include "Systems/Logger.h"
#include "GameFramework/ECS/ComponentHandle.h"

//...

namespace bm = Brahmanda;

void TestObject01::Construct()
{
	bm::ComponentHandle<bm::ObjectTransform> Comp = CreateSubobject<Brahmanda::ObjectTransform>();
	Comp->Rot[1] = 45.f;
	Logger::Info("TEST INFO: {}, {}, {}", Comp->Pos[0], Comp->Rot[1], Comp->Scale[2]);
}

TestObject01::~TestObject01()
{

}