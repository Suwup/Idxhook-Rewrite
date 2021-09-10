#pragma once

#include "Idxhook/Core/Base.h"

#include "Idxhook/Engine/Engine.h"

#include <array>

namespace Idxhook {

	class Cheat
	{
	public:
		using BoneID = UnityEngine::HumanBodyBones;
	public:
		Cheat();
		virtual ~Cheat();

		void Run();
		void Close();

		static inline Cheat& Get() { return *s_Instance; }
	private:
		struct BoneParams
		{
			UnityEngine::Vector2 A = {};
			UnityEngine::Vector2 B = {};
			bool Valid = false;
		};
	public:
		static bool& BlockFuseBox() { return Get().IBlockFuseBox(); }
		static float& FieldOfView() { return Get().IFieldOfView(); }
		static UnityEngine::Vector2& ScreenSize() { return Get().IScreenSize(); }
		static std::array<BoneParams, 16>& Bones() { return Get().IBones(); }
		static std::array<std::pair<BoneID, BoneID>, 16>& BoneIDArray() { return Get().IBoneIDArray(); }
	private:
		struct Hooks
		{
			struct GhostAI { static inline void Start(void* This, MethodInfo* Info); };
			struct DNAEvidence { static inline void Start(void* This, MethodInfo* Info); };
			struct LevelController { static inline void Start(void* This, MethodInfo* Info); };
			struct GameController { static inline void Exit(void* This, MethodInfo* Info); };
			struct PauseMenuController { static inline void Leave(void* This, MethodInfo* Info); };
			struct RewardManager { static inline void Awake(void* This, MethodInfo* Info); };

			struct SceneManager
			{
				static inline void LoadScene(System::String* Name, MethodInfo* Info);
				static inline void SceneLoaded(UnityEngine::Scene Scene, int Mode, MethodInfo* Info);
			};

			struct FuseBox
			{
				static inline void Use(void* This, MethodInfo* Info);
				static inline void TurnOff(void* This, bool Unknown, MethodInfo* Info);
			};

			struct GUIUtility { static inline void CheckOnGUI(MethodInfo* Info); };
			struct Player { static inline void Update(Engine::Player* Player, MethodInfo* Info); };
		};
		
		struct Original
		{
			struct GhostAI { static inline std::add_pointer_t<void(void*, MethodInfo*)> Start = nullptr; };
			struct DNAEvidence { static inline std::add_pointer_t<void(void*, MethodInfo*)> Start = nullptr; };
			struct LevelController { static inline std::add_pointer_t<void(void*, MethodInfo*)> Start = nullptr; };
			struct GameController { static inline std::add_pointer_t<void(void*, MethodInfo*)> Exit = nullptr; };
			struct PauseMenuController { static inline std::add_pointer_t<void(void*, MethodInfo*)> Leave = nullptr; };
			struct RewardManager { static inline std::add_pointer_t<void(void*, MethodInfo*)> Awake = nullptr; };

			struct SceneManager
			{
				static inline std::add_pointer_t<void(System::String*, MethodInfo*)> LoadScene = nullptr;
				static inline std::add_pointer_t<void(UnityEngine::Scene, int, MethodInfo*)> SceneLoaded = nullptr;
			};

			struct FuseBox
			{
				static inline std::add_pointer_t<void(void*, MethodInfo*)> Use = nullptr;
				static inline std::add_pointer_t<void(void*, bool, MethodInfo*)> TurnOff = nullptr;
			};

			struct GUIUtility { static inline std::add_pointer_t<void(MethodInfo*)> CheckOnGUI = nullptr; };
			struct Player { static inline std::add_pointer_t<void(Engine::Player*, MethodInfo*)> Update = nullptr; };
		};
	private:
		bool& IBlockFuseBox() { return m_BlockFuseBox; }
		float& IFieldOfView() { return m_FieldOfView; }
		UnityEngine::Vector2& IScreenSize() { return m_ScreenSize; }
		std::array<BoneParams, 16>& IBones() { return m_Bones; }
		std::array<std::pair<BoneID, BoneID>, 16>& IBoneIDArray() { return m_BoneIDArray; }
	private:
		bool m_BlockFuseBox = false;
		float m_FieldOfView = 0.0f;
		UnityEngine::Vector2 m_ScreenSize = {};

		std::array<BoneParams, 16> m_Bones = {};
		std::array<std::pair<BoneID, BoneID>, 16> m_BoneIDArray =
		{ {
			{ BoneID::Head, BoneID::UpperChest },
			{ BoneID::UpperChest, BoneID::Hips  },
			{ BoneID::Hips, BoneID::LeftUpperLeg },
			{ BoneID::Hips, BoneID::RightUpperLeg },
			{ BoneID::LeftUpperLeg, BoneID::LeftLowerLeg },
			{ BoneID::RightUpperLeg, BoneID::RightLowerLeg },
			{ BoneID::LeftLowerLeg, BoneID::LeftFoot },
			{ BoneID::RightLowerLeg, BoneID::RightFoot },
			{ BoneID::UpperChest, BoneID::LeftShoulder },
			{ BoneID::UpperChest, BoneID::RightShoulder },
			{ BoneID::LeftShoulder, BoneID::LeftUpperArm },
			{ BoneID::RightShoulder, BoneID::RightUpperArm },
			{ BoneID::LeftUpperArm, BoneID::LeftLowerArm },
			{ BoneID::RightUpperArm, BoneID::RightLowerArm },
			{ BoneID::LeftLowerArm, BoneID::LeftHand },
			{ BoneID::RightLowerArm, BoneID::RightHand }
		} };
	private:
		static Cheat* s_Instance;
	};


}
