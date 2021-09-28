/* Make sure that you DON'T use the preprocessor statement "pragma once" or our values will not be set from Cheat.cpp.
Because of this, we need to be careful to not include this file in any other places than Base.h & Cheat.cpp */

////////////////////////////////////
/////// Methods ////////////////////
////////////////////////////////////

OFFSET_METHOD(Screen, get_width, "UnityEngine.");
OFFSET_METHOD(Screen, get_height, "UnityEngine.");

OFFSET_METHOD(Renderer, get_enabled, "UnityEngine.");
OFFSET_METHOD(Renderer, set_enabled, "UnityEngine.");

OFFSET_METHOD(Camera, get_main, "UnityEngine.");
OFFSET_METHOD(Camera, get_fieldOfView, "UnityEngine.");
OFFSET_METHOD(Camera, set_fieldOfView, "UnityEngine.");
OFFSET_METHOD(Camera, WorldToScreenPoint, "UnityEngine.");

OFFSET_METHOD(Component, get_transform, "UnityEngine.");

OFFSET_METHOD(Transform, get_position, "UnityEngine.");
OFFSET_METHOD(Transform, set_position, "UnityEngine.");
OFFSET_METHOD(Transform, TransformDirection, "UnityEngine.");
OFFSET_METHOD(Transform, TransformPoint, "UnityEngine.");

OFFSET_METHOD(Vector3, Distance, "UnityEngine.");
OFFSET_METHOD(Vector3, Magnitude, "UnityEngine.");
OFFSET_METHOD(Vector3, op_Addition, "UnityEngine.");

OFFSET_METHOD(CharacterController, SimpleMove, "UnityEngine.");
OFFSET_METHOD(CharacterController, get_velocity, "UnityEngine.");

OFFSET_METHOD(Text, get_text, "UnityEngine.UI.");

OFFSET_METHOD(Scene, GetBuildIndexInternal, "UnityEngine.SceneManagement.");

OFFSET_METHOD(Animator, GetFloat, "UnityEngine.");
OFFSET_METHOD(Animator, SetFloat, "UnityEngine.");
OFFSET_METHOD(Animator, GetBool, "UnityEngine.");
OFFSET_METHOD(Animator, SetBool, "UnityEngine.");
OFFSET_METHOD(Animator, GetInteger, "UnityEngine.");
OFFSET_METHOD(Animator, SetInteger, "UnityEngine.");
OFFSET_METHOD(Animator, GetBoneTransform, "UnityEngine.");

OFFSET_METHOD(Rigidbody, set_mass, "UnityEngine.");

OFFSET_METHOD(PhotonNetwork, set_NickName, "Photon.Pun.");
OFFSET_METHOD(PhotonNetwork, get_IsMasterClient, "Photon.Pun.");

OFFSET_METHOD(PhotonView, RPC, "Photon.Pun.");

OFFSET_METHOD(Marshal, PtrToStringAnsi, "System.Runtime.InteropServices.");

OFFSET_METHOD(Mission, Completed);

OFFSET_METHOD(GhostAI, Appear);
OFFSET_METHOD(GhostAI, RandomEvent);
OFFSET_METHOD(GhostAI, ChangeState);

OFFSET_METHOD(GhostActivity, Interact);
OFFSET_METHOD(GhostActivity, InteractWithARandomDoor);

////////////////////////////////////
/////// TypeInfo ///////////////////
////////////////////////////////////

OFFSET_TYPE_INFO(GameController);
OFFSET_TYPE_INFO(EvidenceController);
OFFSET_TYPE_INFO(MissionManager);
OFFSET_TYPE_INFO(GhostController);

////////////////////////////////////
/////// Hooks //////////////////////
////////////////////////////////////

OFFSET_HOOK(GUIUtility, CheckOnGUI, "UnityEngine.");

OFFSET_HOOK(GhostAI, Start);

OFFSET_HOOK(DNAEvidence, Start);

OFFSET_HOOK(LevelController, Start);

OFFSET_HOOK(GameController, Exit);

OFFSET_HOOK(PauseMenuController, Leave);

OFFSET_HOOK(RewardManager, Awake);

OFFSET_HOOK(Player, Update);

OFFSET_HOOK(SceneManager, LoadScene, "UnityEngine.SceneManagement.");
OFFSET_HOOK(SceneManager, Internal_SceneLoaded, "UnityEngine.SceneManagement.");

OFFSET_HOOK(FuseBox, TurnOff);
OFFSET_HOOK(FuseBox, Use);
