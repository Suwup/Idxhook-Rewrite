#if 0

/* Make sure that you DON'T use the preprocessor statement "pragma once" or our values will not be set from Cheat.cpp.
Because of this, we need to be careful to not include this file in any other places than Base.h & Cheat.cpp */

////////////////////////////////////
/////// TypeInfo ///////////////////
////////////////////////////////////

OFFSET_TYPE_INFO(GameController, ("Assembly-CSharp", "", "GameController"));
OFFSET_TYPE_INFO(EvidenceController, ("Assembly-CSharp", "", "EvidenceController"));
OFFSET_TYPE_INFO(MissionManager, ("Assembly-CSharp", "", "MissionManager"));
OFFSET_TYPE_INFO(GhostController, ("Assembly-CSharp", "", "GhostController"));

////////////////////////////////////
/////// Hooks //////////////////////
////////////////////////////////////

OFFSET_HOOK(GUIUtility, CheckOnGUI, ("UnityEngine.CoreModule", "UnityEngine", "GUIUtility", "CheckOnGUI", 0));

OFFSET_HOOK(GhostAI, Start, ("Assembly-CSharp", "", "GhostAI", "Start", 0));

OFFSET_HOOK(DNAEvidence, Start, ("Assembly-CSharp", "", "DNAEvidence", "Start", 0));

OFFSET_HOOK(LevelController, Start, ("Assembly-CSharp", "", "LevelController", "Start", 0));

OFFSET_HOOK(GameController, Exit, ("Assembly-CSharp", "", "GameController", "Exit", 0));

OFFSET_HOOK(PauseMenuController, Leave, ("Assembly-CSharp", "", "PauseMenuController", "Leave", 0));

OFFSET_HOOK(RewardManager, Awake, ("Assembly-CSharp", "", "RewardManager", "Awake", 0));

OFFSET_HOOK(Player, Update, ("Assembly-CSharp", "", "Player", "Update", 0));

OFFSET_HOOK(SceneManager, LoadScene, ("UnityEngine", "SceneManagement", "SceneManager", "LoadScene", 1));
OFFSET_HOOK(SceneManager, Internal_SceneLoaded, ("UnityEngine", "SceneManagement", "SceneManager", "Internal_SceneLoaded", 2));

OFFSET_HOOK(FuseBox, TurnOff, ("Assembly-CSharp", "", "FuseBox", "TurnOff", 1));
OFFSET_HOOK(FuseBox, Use, ("Assembly-CSharp", "", "FuseBox", "Use", 0));

#endif
