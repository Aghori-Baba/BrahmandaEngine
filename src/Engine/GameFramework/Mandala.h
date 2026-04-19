// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <cstdint>
#include <array>
#include <type_traits>
#include <cassert>

#include "GameConfig.h"
#include "WorldLayer.h"
#include "WorldLayerCollection.h"
#include "LayerContextData.h"
#include "SessionMaster.h"

//...

namespace Brahmanda
{
	class FrameContextData;
	class WorldLayer;
	class AssetManager;
	class CameraManager;
	class WorldCamera;
	class InputManager;

	struct WorldConfig
	{
	public:

		WorldConfig()
		{

		}

		~WorldConfig()
		{

		}

	private:

	};

	struct ManadalaInitializerData
	{
		AssetManager* AssetMgr;
	};

	class Mandala
	{
	public:

		using PARENT = Brahmanda::Mandala;

		Mandala();
		virtual ~Mandala();

		void Construct(ManadalaInitializerData Initializer);
		void Init();
		virtual void OnInit();
		virtual void PostInit();

		void Cycle(float DeltaTime, FrameContextData& InContext);
		virtual void OnCycle(float DeltaTime);

		void Shutdown();
		virtual void OnShutdown();

		void SetWorldConfig(const WorldConfig& InConfig);

		template<typename T>
		inline bool StartNewSession()
		{
			static_assert(std::is_base_of_v<SessionMaster, T>, "T must derive from SessionMaster");

			if (bIsSessionCreated)
			{
				ActiveSession->ExitSession();
				ActiveSession.reset();
			}

			ActiveSession = CreateNewSession<T>();
			if (ActiveSession)
			{
				ActiveSession->EnterSession();
				bIsSessionCreated = true;

				LayerData.CurrentSession = ActiveSession.get();

				return true;
			}

			return false;
		}

		template<typename T>
		void CreateInputManager()
		{
			static_assert(std::is_base_of_v<InputManager, T>, "T must derive from InputManager");

			bIsInputManagerCreated = true;
			InputManagerRef = std::make_unique<T>();
			InputManagerRef->Construct(CameraManagerRef.get());

			LayerData.InputMgr = InputManagerRef.get();
		}

	private:

		template<typename T>
		inline std::unique_ptr<T> CreateNewSession()
		{
			static_assert(std::is_base_of_v<SessionMaster, T>, "T must derive from SessionMaster");

			return std::make_unique<T>();
		}

	protected:

		WorldLayerCollection<Config::World::MAX_WORLD_LAYER_COUNT> Collection;
		LayerContextData LayerData;

	private:

		bool bIsSessionCreated = false;
		bool bIsInputManagerCreated = false;
		uint16_t ActiveWorldLayerCount = 0;

		AssetManager* AssetManager = nullptr;

		std::unique_ptr<SessionMaster> ActiveSession;
		std::unique_ptr<CameraManager> CameraManagerRef;
		std::unique_ptr<InputManager> InputManagerRef;

		RenderGroup2D GlobalRenderable2DList;
		std::vector<RenderItem2D*> GlobalData;

		//TEST CODE:
		//std::unique_ptr<WorldCamera> TEST_Cam = nullptr;
	};
}