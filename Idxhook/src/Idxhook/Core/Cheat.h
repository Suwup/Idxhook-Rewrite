#pragma once

#include "Idxhook/Core/Base.h"

#include "Idxhook/Engine/Engine.h"

#include <array>
#include <imgui.h>
#undef DrawText

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
		struct BaseParams
		{
			bool Valid = false;
		};

		struct BoneParams : public BaseParams
		{
			UnityEngine::Vector2 A = {};
			UnityEngine::Vector2 B = {};
		};

		struct ItemParams : public BaseParams
		{
			UnityEngine::Vector2 Location = {};
			const char* Name = nullptr;
		};
	private:
		enum class EBox : int32_t
		{
			ENone,
			E2DBoxes,
			E3DBoxes
		};
	public:
		static bool& xQcSpeed() { return Get().IxQcSpeed(); }
		static float& xQcSpeedMultiplier() { return Get().IxQcSpeedMultiplier(); }
		static bool& Credits() { return Get().ICredits(); }
		static bool& BlockFuseBox() { return Get().IBlockFuseBox(); }
		static float& FieldOfView() { return Get().IFieldOfView(); }
		static bool& ItemEnable() { return Get().IItemEnable(); }
		static bool& GhostEnable() { return Get().IGhostEnable(); }
		static bool& GhostSkeleton() { return Get().IGhostSkeleton(); }
		static UnityEngine::Vector2& ScreenSize() { return Get().IScreenSize(); }
		static EBox& GhostBoxType() { return Get().IGhostBoxType(); }
		static std::array<BoneParams, 16>& Bones() { return Get().IBones(); }
		static std::array<ItemParams, 15>& Items() { return Get().IItems(); }
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
		bool& IxQcSpeed() { return m_xQcSpeed; }
		float& IxQcSpeedMultiplier() { return m_xQcSpeedMultiplier; }
		bool& ICredits() { return m_Credits; }
		bool& IBlockFuseBox() { return m_BlockFuseBox; }
		float& IFieldOfView() { return m_FieldOfView; }
		bool& IItemEnable() { return m_ItemEnable; }
		bool& IGhostEnable() { return m_GhostEnable; }
		bool& IGhostSkeleton() { return m_GhostSkeleton; }
		UnityEngine::Vector2& IScreenSize() { return m_ScreenSize; }
		EBox& IGhostBoxType() { return m_GhostBoxType; }
		std::array<BoneParams, 16>& IBones() { return m_Bones; }
		std::array<ItemParams, 15>& IItems() { return m_Items; }
		std::array<std::pair<BoneID, BoneID>, 16>& IBoneIDArray() { return m_BoneIDArray; }
	private:
		bool m_xQcSpeed = false;
		float m_xQcSpeedMultiplier = 0.0f;
		bool m_Credits = true;
		bool m_BlockFuseBox = false;
		float m_FieldOfView = 0.0f;
		bool m_ItemEnable = true;
		bool m_GhostEnable = true;
		bool m_GhostSkeleton = true;

		UnityEngine::Vector2 m_ScreenSize = {};

		EBox m_GhostBoxType = EBox::ENone;
		std::array<BoneParams, 16> m_Bones = {};
		std::array<ItemParams, 15> m_Items = {};
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
