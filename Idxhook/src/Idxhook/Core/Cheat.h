#pragma once

#include "Idxhook/Core/Base.h"

#include "Idxhook/Engine/Engine.h"

#include <unordered_map>
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
			UnityEngine::Vector2 A{};
			UnityEngine::Vector2 B{};
		};

		struct ItemParams : public BaseParams
		{
			UnityEngine::Vector2 Location{};
			const char* Name = nullptr;
		};

		struct BoxParams : public BaseParams
		{
			UnityEngine::Vector2 Location[2][4]{};
		};

		using NameParams = ItemParams;
	private:
		static constexpr int32_t s_MaxArraySize = 32;
		static constexpr int32_t s_BoneCount = 18;
	public:
		static constexpr int32_t MaxArraySize() { return s_MaxArraySize; }
		static constexpr int32_t BoneCount() { return s_BoneCount; }
	public:
		static bool& xQcSpeed() { return Get().IxQcSpeed(); }
		static float& xQcSpeedMultiplier() { return Get().IxQcSpeedMultiplier(); }
		static bool& Credits() { return Get().ICredits(); }
		static bool& BlockFuseBox() { return Get().IBlockFuseBox(); }
		static float& FieldOfView() { return Get().IFieldOfView(); }
		static bool& ItemEnable() { return Get().IItemEnable(); }
		static bool& PlayersEnable() { return Get().IPlayersEnable(); }
		static bool& PlayersSkeletonEnable() { return Get().IPlayersSkeletonEnable(); }
		static bool& PlayersNameEnable() { return Get().IPlayersNameEnable(); }
		static bool& GhostEnable() { return Get().IGhostEnable(); }
		static bool& GhostBoxEnable() { return Get().IGhostBoxEnable(); }
		static bool& GhostSkeletonEnable() { return Get().IGhostSkeletonEnable(); }
		static bool& GhostRenderModel() { return Get().IGhostRenderModel(); }
		static bool& GhostShouldRenderModel() { return Get().IGhostShouldRenderModel(); }
		static bool& MaxStamina() { return Get().IMaxStamina(); }
		static bool& MaxSanity() { return Get().IMaxSanity(); }
		static UnityEngine::Vector2& ScreenSize() { return Get().IScreenSize(); }
		static BoxParams& GhostBox() { return Get().IGhostBox(); }
		static std::array<BoneParams, s_BoneCount>& GhostBones() { return Get().IGhostBones(); }
		static std::array<std::array<BoneParams, s_BoneCount>, s_MaxArraySize>& PlayerBones() { return Get().IPlayerBones(); }
		static std::array<NameParams, s_MaxArraySize>& PlayerNames() { return Get().IPlayerNames(); }
		static std::array<ItemParams, s_MaxArraySize>& Items() { return Get().IItems(); }
		static std::array<std::pair<BoneID, BoneID>, s_BoneCount>& BoneIDArray() { return Get().IBoneIDArray(); }
		static std::unordered_map<std::string, uintptr_t>& FunctionMap() { return Get().IFunctionMap(); }
		static std::unordered_map<std::string, uintptr_t>& TypeInfoMap() { return Get().ITypeInfoMap(); }
	private:
		struct Hooks
		{
			struct GhostAI { static inline void Start(void* This, void* Info); };
			struct DNAEvidence { static inline void Start(void* This, void* Info); };
			struct LevelController { static inline void Start(void* This, void* Info); };
			struct GameController { static inline void Exit(void* This, void* Info); };
			struct PauseMenuController { static inline void Leave(void* This, void* Info); };
			struct RewardManager { static inline void Awake(void* This, void* Info); };
			struct SceneManager { static inline void LoadScene(System::String* Name, void* Info); };

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
			struct SceneManager { static inline std::add_pointer_t<void(System::String*, void*)> LoadScene = nullptr; };

			struct FuseBox
			{
				static inline std::add_pointer_t<void(void*, void*)> Use = nullptr;
				static inline std::add_pointer_t<void(void*, bool, void*)> TurnOff = nullptr;
			};

			struct GUIUtility { static inline std::add_pointer_t<void(void*)> CheckOnGUI = nullptr; };
			struct Player { static inline std::add_pointer_t<void(Engine::Player*, void*)> Update = nullptr; };
		};
	private:
		bool& IxQcSpeed() { return m_xQcSpeed; }
		float& IxQcSpeedMultiplier() { return m_xQcSpeedMultiplier; }
		bool& ICredits() { return m_Credits; }
		bool& IBlockFuseBox() { return m_BlockFuseBox; }
		float& IFieldOfView() { return m_FieldOfView; }
		bool& IItemEnable() { return m_ItemEnable; }
		bool& IPlayersEnable() { return m_PlayersEnable; }
		bool& IPlayersSkeletonEnable() { return m_PlayersSkeletonEnable; }
		bool& IPlayersNameEnable() { return m_PlayersNameEnable; }
		bool& IGhostEnable() { return m_GhostEnable; }
		bool& IGhostBoxEnable() { return m_GhostBoxEnable; }
		bool& IGhostSkeletonEnable() { return m_GhostSkeletonEnable; }
		bool& IGhostRenderModel() { return m_GhostRenderModel; }
		bool& IGhostShouldRenderModel() { return m_GhostShouldRenderModel; }
		bool& IMaxStamina() { return m_MaxStamina; }
		bool& IMaxSanity() { return m_MaxSanity; }
		UnityEngine::Vector2& IScreenSize() { return m_ScreenSize; }
		BoxParams& IGhostBox() { return m_GhostBox; }
		std::array<BoneParams, s_BoneCount>& IGhostBones() { return m_GhostBones; }
		std::array<std::array<BoneParams, s_BoneCount>, s_MaxArraySize>& IPlayerBones() { return m_PlayerBones; }
		std::array<NameParams, s_MaxArraySize>& IPlayerNames() { return m_PlayerNames; }
		std::array<ItemParams, s_MaxArraySize>& IItems() { return m_Items; }
		std::array<std::pair<BoneID, BoneID>, s_BoneCount>& IBoneIDArray() { return m_BoneIDArray; }
		std::unordered_map<std::string, uintptr_t>& IFunctionMap() { return m_FunctionMap; }
		std::unordered_map<std::string, uintptr_t>& ITypeInfoMap() { return m_TypeInfoMap; }
	private:
		bool m_xQcSpeed = false;
		float m_xQcSpeedMultiplier = 1.0f;
		bool m_Credits = true;
		bool m_BlockFuseBox = false;
		float m_FieldOfView = 0.0f;
		bool m_ItemEnable = true;
		bool m_PlayersEnable = true;
		bool m_PlayersSkeletonEnable = true;
		bool m_PlayersNameEnable = true;
		bool m_GhostEnable = true;
		bool m_GhostBoxEnable = true;
		bool m_GhostSkeletonEnable = true;
		bool m_GhostRenderModel = true;
		bool m_GhostShouldRenderModel = true;
		bool m_MaxStamina = true;
		bool m_MaxSanity = true;

		UnityEngine::Vector2 m_ScreenSize{};

		BoxParams m_GhostBox{};
		std::array<std::array<BoneParams, s_BoneCount>, s_MaxArraySize> m_PlayerBones{};
		std::array<BoneParams, s_BoneCount> m_GhostBones{};
		std::array<ItemParams, s_MaxArraySize> m_PlayerNames{};
		std::array<ItemParams, s_MaxArraySize> m_Items{};
		std::array<std::pair<BoneID, BoneID>, s_BoneCount> m_BoneIDArray =
		{ {
			{ BoneID::Head, BoneID::UpperChest },
			{ BoneID::UpperChest, BoneID::Hips  },
			{ BoneID::Hips, BoneID::LeftUpperLeg },
			{ BoneID::Hips, BoneID::RightUpperLeg },
			{ BoneID::LeftUpperLeg, BoneID::LeftLowerLeg },
			{ BoneID::RightUpperLeg, BoneID::RightLowerLeg },
			{ BoneID::LeftLowerLeg, BoneID::LeftFoot },
			{ BoneID::RightLowerLeg, BoneID::RightFoot },
			{ BoneID::LeftFoot, BoneID::LeftToes },
			{ BoneID::RightFoot, BoneID::RightToes },
			{ BoneID::UpperChest, BoneID::LeftShoulder },
			{ BoneID::UpperChest, BoneID::RightShoulder },
			{ BoneID::LeftShoulder, BoneID::LeftUpperArm },
			{ BoneID::RightShoulder, BoneID::RightUpperArm },
			{ BoneID::LeftUpperArm, BoneID::LeftLowerArm },
			{ BoneID::RightUpperArm, BoneID::RightLowerArm },
			{ BoneID::LeftLowerArm, BoneID::LeftHand },
			{ BoneID::RightLowerArm, BoneID::RightHand }
		} };

		std::unordered_map<std::string, uintptr_t> m_FunctionMap{};
		std::unordered_map<std::string, uintptr_t> m_TypeInfoMap{};
	private:
		static Cheat* s_Instance;
	};


}
