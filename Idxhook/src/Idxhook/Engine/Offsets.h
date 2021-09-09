#pragma once

namespace Idxhook::Offsets {

#define OFFSET(name, offset) inline std::uintptr_t name = Memory::GetRVA(offset)
#define OFFSET_PTR(name, offset) inline void* name = Memory::GetRVAPointer<void>(offset)

    namespace Methods {

        namespace Screen {

			OFFSET(GetWidth, 11903344); /* int32_t UnityEngine_Screen__get_width (const MethodInfo* method); */
			OFFSET(GetHeight, 11903248); /* int32_t UnityEngine_Screen__get_height (const MethodInfo* method); */

        }

        namespace Camera {

            OFFSET(GetMain, 11527120); /* UnityEngine_Camera_o* UnityEngine_Camera__get_main (const MethodInfo* method); */
            OFFSET(GetFieldOfView, 11526992); /* float UnityEngine_Camera__get_fieldOfView (UnityEngine_Camera_o* __this, const MethodInfo* method); */
            OFFSET(SetFieldOfView, 11530256); /* void UnityEngine_Camera__set_fieldOfView (UnityEngine_Camera_o* __this, float value, const MethodInfo* method); */
            OFFSET(WorldToScreenPoint, 11525328); /* UnityEngine_Vector3_o UnityEngine_Camera__WorldToScreenPoint (UnityEngine_Camera_o* __this, UnityEngine_Vector3_o position, const MethodInfo* method); */

        }

        namespace Component { inline std::uintptr_t GetTransform = Memory::GetRVA(11538912); } /* UnityEngine_Transform_o* UnityEngine_Component__get_transform (UnityEngine_Component_o* __this, const MethodInfo* method); */

        namespace Transform {

			OFFSET(GetPosition, 11950256); /* UnityEngine_Vector3_o UnityEngine_Transform__get_position (UnityEngine_Transform_o* __this, const MethodInfo* method); */
			OFFSET(SetPosition, 11952624); /* void UnityEngine_Transform__set_position (UnityEngine_Transform_o* __this, UnityEngine_Vector3_o value, const MethodInfo* method); */
			OFFSET(TransformDirection, 11947264); /* UnityEngine_Vector3_o UnityEngine_Transform__TransformDirection (UnityEngine_Transform_o* __this, UnityEngine_Vector3_o direction, const MethodInfo* method); */

        }

        namespace Vector3 {

			OFFSET(Distance, 17021136); /* float UnityEngine_Vector3__Distance (UnityEngine_Vector3_o a, UnityEngine_Vector3_o b, const MethodInfo* method); */
			OFFSET(Addition, 17030592); /* UnityEngine_Vector3_o UnityEngine_Vector3__op_Addition (UnityEngine_Vector3_o a, UnityEngine_Vector3_o b, const MethodInfo* method); */

        }

		namespace Text { OFFSET(GetText, 3075760); } /* System_String_o* UnityEngine_UI_Text__get_text (UnityEngine_UI_Text_o* __this, const MethodInfo* method); */
		namespace Scene { OFFSET(GetBuildIndexInternal, 11901296); } /* int32_t UnityEngine_SceneManagement_Scene__GetBuildIndexInternal (int32_t sceneHandle, const MethodInfo* method); */
		namespace Animator { OFFSET(GetBoneTransform, 17392960); } /* UnityEngine_Transform_o* UnityEngine_Animator__GetBoneTransform (UnityEngine_Animator_o* __this, int32_t humanBoneId, const MethodInfo* method); */
		namespace Rigidbody { OFFSET(SetMass, 17339696); } /* void UnityEngine_Rigidbody__set_mass (UnityEngine_Rigidbody_o* __this, float value, const MethodInfo* method); */
		namespace PhotonNetwork { OFFSET(SetNickName, 6643744); } /* void Photon_Pun_PhotonNetwork__set_NickName (System_String_o* value, const MethodInfo* method); */
		namespace PhotonView { OFFSET(RPC, 44853488); } /* void Photon_Pun_PhotonView__RPC (Photon_Pun_PhotonView_o* __this, System_String_o* methodName, int32_t target, System_Object_array* parameters, const MethodInfo* method); */
		namespace Marshal { OFFSET(PtrToStringAnsi, 5254912); } /* System_String_o* System_Runtime_InteropServices_Marshal__PtrToStringAnsi (intptr_t ptr, const MethodInfo* method); */
		namespace Mission { OFFSET(Completed, 33125376); } /* void Mission__Completed (Mission_o* __this, const MethodInfo* method); */

        namespace GhostAI {

			OFFSET(Appear, 18764416); /* void GhostAI__Appear (GhostAI_o* __this, bool ___________, const MethodInfo* method); */
			OFFSET(RandomEvent, 18768960); /* void GhostAI__RandomEvent (GhostAI_o* __this, const MethodInfo* method); */

        }

        namespace GhostActivity {

			OFFSET(Interact, 18788944); /* void GhostActivity__Interact (GhostActivity_o* __this, const MethodInfo* method); */
			OFFSET(InteractWithARandomDoor, 18786448); /* bool GhostActivity__InteractWithARandomDoor (GhostActivity_o* __this, const MethodInfo* method); */

        }
    }

    namespace TypeInfo {

		OFFSET(GameController, 56280704); /* GameController_c* */
		OFFSET(EvidenceController, 56280160); /* EvidenceController_c* */
		OFFSET(MissionManager, 56278200); /* MissionManager_c* */
		OFFSET(GhostController, 56275672); /* GhostController_c* */

    }

    namespace Hooks {

        namespace GUIUtility { OFFSET_PTR(CheckOnGUI, 17142496); } /* void UnityEngine_GUIUtility__CheckOnGUI (const MethodInfo* method); */
        namespace GhostAI { OFFSET_PTR(Start, 18770800); } /* void GhostAI__Start (GhostAI_o* __this, const MethodInfo* method); */
        namespace DNAEvidence { OFFSET_PTR(Start, 34393632); } /* void DNAEvidence__Start (DNAEvidence_o* __this, const MethodInfo* method); */
        namespace LevelController { OFFSET_PTR(Start, 21922464); } /* void LevelController__Start (LevelController_o* __this, const MethodInfo* method); */
        namespace GameController { OFFSET_PTR(Exit, 18694768); } /* void GameController__Exit (GameController_o* __this, const MethodInfo* method); */
        namespace PauseMenuController { OFFSET_PTR(Leave, 25872032); } /* void PauseMenuController__Leave (PauseMenuController_o* __this, const MethodInfo* method); */
        namespace RewardManager { OFFSET_PTR(Awake, 30304528); } /* void RewardManager__Awake (RewardManager_o* __this, const MethodInfo* method); */
        namespace Player { OFFSET_PTR(Update, 24723248); } /* void Player__Update (Player_o* __this, const MethodInfo* method); */

        namespace SceneManager {

            OFFSET_PTR(LoadScene, 11899888); /* void UnityEngine_SceneManagement_SceneManager__LoadScene (System_String_o* sceneName, const MethodInfo* method); */
            OFFSET_PTR(SceneLoaded, 11897984); /* void UnityEngine_SceneManagement_SceneManager__Internal_SceneLoaded (UnityEngine_SceneManagement_Scene_o scene, int32_t mode, const MethodInfo* method); */

        }

        namespace FuseBox {

            OFFSET_PTR(Use, 33713248); /* void FuseBox__Use (FuseBox_o* __this, const MethodInfo* method); */
            OFFSET_PTR(TurnOff, 33678224); /* void FuseBox__TurnOff (FuseBox_o* __this, bool ___________, const MethodInfo* method); */

        }

    }

}
