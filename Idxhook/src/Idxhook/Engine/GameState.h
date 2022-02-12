#pragma once
#include "UnityEngine.h"

#include <array>

namespace Idxhook {

	namespace GameState {

		// TODO: Move to Cheat class

		namespace Pointers {

			inline void* GhostAI = nullptr;
			inline void* DNAEvidence = nullptr;
			inline void* LevelController = nullptr;

			static constexpr auto ResetPointers = []() -> void { GhostAI = DNAEvidence = LevelController = nullptr; };
			static constexpr auto CheckPointers = []() -> bool { return GhostAI && DNAEvidence && LevelController; };

		}

	}

}
