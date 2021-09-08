#pragma once

#include "Idxhook/Core/Base.h"

#include "Idxhook/Engine/Engine.h"

namespace Idxhook {

	class Cheat
	{
	public:
		Cheat();
		virtual ~Cheat();

		void Run();
		void Close();

		static inline Cheat& Get() { return *s_Instance; }
	public:
		static bool& BlockFuseBox() { return Get().IBlockFuseBox(); }
		static float& FieldOfView() { return Get().IFieldOfView(); }
	private:
		struct Hooks
		{
			struct GhostAI { static inline void Start(void* This, void* Info); };
			struct DNAEvidence { static inline void Start(void* This, void* Info); };
			struct LevelController { static inline void Start(void* This, void* Info); };
			struct GameController { static inline void Exit(void* This, void* Info); };
			struct PauseMenuController { static inline void Leave(void* This, void* Info); };
			struct RewardManager { static inline void Awake(void* This, void* Info); };

			struct SceneManager
			{
				static inline void LoadScene(System::String* Name, void* Info);
				static inline void SceneLoaded(UnityEngine::Scene Scene, int Mode, void* Info);
			};

			struct FuseBox
			{
				static inline void Use(void* This, void* Info);
				static inline void TurnOff(void* This, bool Unknown, void* Info);
			};

			struct GUIUtility { static inline void CheckOnGUI(void* Info); };
			struct Player { static inline void Update(Engine::Player* Player, void* Info); };
		};
		
		struct Original
		{
			struct GhostAI { static inline std::add_pointer_t<void(void*, void*)> Start = nullptr; };
			struct DNAEvidence { static inline std::add_pointer_t<void(void*, void*)> Start = nullptr; };
			struct LevelController { static inline std::add_pointer_t<void(void*, void*)> Start = nullptr; };
			struct GameController { static inline std::add_pointer_t<void(void*, void*)> Exit = nullptr; };
			struct PauseMenuController { static inline std::add_pointer_t<void(void*, void*)> Leave = nullptr; };
			struct RewardManager { static inline std::add_pointer_t<void(void*, void*)> Awake = nullptr; };

			struct SceneManager
			{
				static inline std::add_pointer_t<void(System::String*, void*)> LoadScene = nullptr;
				static inline std::add_pointer_t<void(UnityEngine::Scene, int, void*)> SceneLoaded = nullptr;
			};

			struct FuseBox
			{
				static inline std::add_pointer_t<void(void*, void*)> Use = nullptr;
				static inline std::add_pointer_t<void(void*, bool, void*)> TurnOff = nullptr;
			};

			struct GUIUtility { static inline std::add_pointer_t<void(void*)> CheckOnGUI = nullptr; };
			struct Player { static inline std::add_pointer_t<void(Engine::Player*, void*)> Update = nullptr; };
		};
	private:
		bool& IBlockFuseBox() { return m_BlockFuseBox; }
		float& IFieldOfView() { return m_FieldOfView; }
	private:
		bool m_BlockFuseBox = false;
		float m_FieldOfView = 0.0f;
	private:
		static Cheat* s_Instance;
	};


}
