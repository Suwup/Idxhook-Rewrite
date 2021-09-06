#pragma once

#include "Idxhook/Core/Base.h"

#include "Idxhook/Engine/Game.h"

namespace Idxhook {

	class Cheat
	{
	public:
		Cheat();
		virtual ~Cheat();

		void Run();
		void Close();

		static inline Cheat& Get() { return *s_Instance; }
	private:
		struct GhostAI { static inline void Start(void* This, void* Info); };
		struct DNAEvidence { static inline void Start(void* This, void* Info); };
		struct LevelController { static inline void Start(void* This, void* Info); };
		struct GameController { static inline void Exit(void* This, void* Info); };
		struct PauseMenuController { static inline void Leave(void* This, void* Info); };
		struct RewardManager { static inline void Awake(void* This, void* Info); };

		struct SceneManager
		{
			static inline void LoadScene(System::String* This, void* Info);
			static inline void SceneLoaded(UnityEngine::Scene Scene, int Mode, void* Info);
		};

		struct FuseBox
		{
			static inline void Use(void* This, void* Info);
			static inline void TurnOff(void* This, bool Unknown, void* Info);
		};

		struct GUIUtility { static inline void CheckOnGUI(void* Info); };
		struct Player { static inline void Update(Game::Player* Player, void* Info); };
	private:
		static Cheat* s_Instance;
	};


}
