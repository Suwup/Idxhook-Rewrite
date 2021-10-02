#pragma once
#include "Idxhook/Engine/Il2cppInternal.h"

namespace Idxhook::Offsets {

	#define CALL_METHOD(type, args, values, sig) static auto fn = reinterpret_cast<type(*)args>(Il2cpp::GetMethod##sig); \
		return fn ## values; \

	#define DEF_TYPE_INFO(name, sig) namespace TypeInfo { inline Il2CppClass* name = nullptr; }
	#define DEF_HOOK(namespaze, name, sig) namespace Hooks::namespaze { inline Il2CppMethodPointer name = nullptr; }
	
	#define USE_TYPE_INFO(type) \
		type(GameController, ("Assembly-CSharp", "", "GameController")) \
		type(EvidenceController, ("Assembly-CSharp", "", "EvidenceController")) \
		type(MissionManager, ("Assembly-CSharp", "", "MissionManager")) \
		type(GhostController, ("Assembly-CSharp", "", "GhostController")) \

	#define USE_HOOK(type) \
		type(GUIUtility, CheckOnGUI, ("UnityEngine.IMGUIModule", "UnityEngine", "GUIUtility", "CheckOnGUI", 0)) \
		type(GhostAI, Start, ("Assembly-CSharp", "", "GhostAI", "Start", 0)) \
		type(DNAEvidence, Start, ("Assembly-CSharp", "", "DNAEvidence", "Start", 0)) \
		type(LevelController, Start, ("Assembly-CSharp", "", "LevelController", "Start", 0)) \
		type(GameController, Exit, ("Assembly-CSharp", "", "GameController", "Exit", 0)) \
		type(PauseMenuController, Leave, ("Assembly-CSharp", "", "PauseMenuController", "Leave", 0)) \
		type(RewardManager, Awake, ("Assembly-CSharp", "", "RewardManager", "Awake", 0)) \
		type(Player, Update, ("Assembly-CSharp", "", "Player", "Update", 0)) \
		type(SceneManager, LoadScene, ("UnityEngine.CoreModule", "UnityEngine.SceneManagement", "SceneManager", "LoadScene", 1)) \
		type(FuseBox, TurnOff, ("Assembly-CSharp", "", "FuseBox", "TurnOff", 1)) \
		type(FuseBox, Use, ("Assembly-CSharp", "", "FuseBox", "Use", 0)) \

	USE_TYPE_INFO(DEF_TYPE_INFO);
	USE_HOOK(DEF_HOOK);

}
