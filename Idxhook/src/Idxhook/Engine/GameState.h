#pragma once
#include "UnityEngine.h"

#include <array>

namespace Idxhook {

	struct Object
	{
		UnityEngine::Vector2 Position;
		bool WorldToScreen;
		int Distance;
		std::string Name;

		std::array<std::pair<UnityEngine::Vector2, UnityEngine::Vector2>, 16> Bones;
		bool BonesWorldToScreen;
	};

	struct Mission
	{
		std::string Label;
		bool IsCompleted;
	};

	namespace GameState {

		inline Object EvidenceData[32];
		inline int32_t EvidenceCount;

		inline Object PlayerData[32];
		inline int32_t PlayerCount;

		inline Mission MissionData[32];
		inline int32_t MissionCount;

		inline Object FuseBox;

		namespace GhostData {

			inline std::string Name;
			inline std::string Age;
			inline std::string Type;
			inline std::string Evidence;
			inline std::string Gender;
			inline std::string Room;
			inline std::string Hunting;
			inline UnityEngine::Vector2 Position;
			inline int Distance;
			inline bool WorldToScreen;
			inline std::array<std::pair<UnityEngine::Vector2, UnityEngine::Vector2>, 16> Bones;
			inline bool BonesWorldToScreen;

		}

		namespace LocalPlayerData {

			inline std::string Sanity;
			inline std::string Hunted;
			inline std::string Room;

		}

		namespace Pointers {

			inline void* GhostAI = nullptr;
			inline void* DNAEvidence = nullptr;
			inline void* LevelController = nullptr;

			static constexpr auto ResetPointers = []() -> void { GhostAI = DNAEvidence = LevelController = nullptr; };
			static constexpr auto CheckPointers = []() -> bool { return GhostAI && DNAEvidence && LevelController; };

		}

	}

}
