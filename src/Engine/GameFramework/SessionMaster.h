// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include "SessionMessenger.h"

//...

namespace Brahmanda
{
	class CameraManager;

	struct SessionData
	{
		uint32_t SessionID = 0;
	};

	class ISessionBridge
	{
	public:

		ISessionBridge() = default;
		virtual ~ISessionBridge() = default;

		//virtual void SendSignal(float InValue) = 0;
	};

	class SessionMaster : public ISessionBridge
	{
	public:

		SessionMaster();
		virtual ~SessionMaster();

		virtual void EnterSession();
		virtual void Cycle(float DeltaTime);
		virtual void ExitSession();

		//Interface Implementation

		//void SendFloatSignal(float InValue) override;

	private:

		SessionData ActiveSessionData = {};
	};
}