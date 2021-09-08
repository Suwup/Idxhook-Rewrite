#pragma once

namespace Idxhook::Offsets {

    namespace Methods {

        namespace Screen {

            inline std::uintptr_t GetWidth = Memory::GetRVA(0xAE2FB0);
            inline std::uintptr_t GetHeight = Memory::GetRVA(0xAE2F50);

        }

        namespace Camera {

            inline std::uintptr_t GetMain = Memory::GetRVA(0xAAA120);
            inline std::uintptr_t GetFieldOfView = Memory::GetRVA(11182240); /* float UnityEngine_Camera__get_fieldOfView (UnityEngine_Camera_o* __this, const MethodInfo* method); */
            inline std::uintptr_t SetFieldOfView = Memory::GetRVA(11185504); /* void UnityEngine_Camera__set_fieldOfView (UnityEngine_Camera_o* __this, float value, const MethodInfo* method); */
            inline std::uintptr_t WorldToScreenPoint /* WorldToScreenPoint_1 */ = Memory::GetRVA(0xAA9A20);

        }

        namespace Component /* Component_1 */ { inline std::uintptr_t GetTransform = Memory::GetRVA(0xAACF30); }

        namespace Transform {

			inline std::uintptr_t GetPosition = Memory::GetRVA(0xAEE6F0);
			inline std::uintptr_t SetPosition = Memory::GetRVA(0xAEF030);
			inline std::uintptr_t TransformDirection = Memory::GetRVA(0xAEDB40);

        }

        namespace Vector3 {

			inline std::uintptr_t Distance = Memory::GetRVA(0xE46A10);
			inline std::uintptr_t Addition = Memory::GetRVA(0xE48F00);

        }

		namespace Text { inline std::uintptr_t GetText = Memory::GetRVA(0x2EDEB0); }
		namespace Scene { inline std::uintptr_t GetBuildIndexInternal = Memory::GetRVA(0xAE27B0); }
		namespace Animator { inline std::uintptr_t GetBoneTransform = Memory::GetRVA(0xEA1680); }
		namespace Rigidbody { inline std::uintptr_t SetMass = Memory::GetRVA(0xE94670); }
		namespace PhotonNetwork { inline std::uintptr_t SetNickName = Memory::GetRVA(0x6270E0); }
		namespace PhotonView { inline std::uintptr_t RPC = Memory::GetRVA(0x2B42EA0); }
		namespace Marshal { inline std::uintptr_t PtrToStringAnsi = Memory::GetRVA(0x4D3FC0); }
		namespace Mission { inline std::uintptr_t Completed = Memory::GetRVA(0x29E3800); }

        namespace GhostAI {

			inline std::uintptr_t Appear = Memory::GetRVA(0xFF9640);
			inline std::uintptr_t RandomEvent = Memory::GetRVA(0xFFA7C0);

        }

        namespace GhostActivity {

			inline std::uintptr_t Interact = Memory::GetRVA(0xFFF770);
			inline std::uintptr_t InteractWithARandomDoor = Memory::GetRVA(0xFFEC80);

        }
    }

    namespace TypeInfo {

		inline std::uintptr_t GameController = Memory::GetRVA(57117384);
		inline std::uintptr_t EvidenceController = Memory::GetRVA(57116832);
		inline std::uintptr_t MissionManager = Memory::GetRVA(57114872);
		inline std::uintptr_t GhostController = Memory::GetRVA(57112376);

    }

    namespace Hooks {

        namespace GUIUtility { inline void* CheckOnGUI = Memory::GetRVAPointer<void>(15090720); } /* void UnityEngine_GUIUtility__CheckOnGUI (const MethodInfo* method); */
        namespace GhostAI { inline void* Start = Memory::GetRVAPointer<void>(16756464); } /* void GhostAI__Start (GhostAI_o* __this, const MethodInfo* method); */
        namespace DNAEvidence { inline void* Start = Memory::GetRVAPointer<void>(33694544); } /* void DNAEvidence__Start (DNAEvidence_o* __this, const MethodInfo* method); */
        namespace LevelController { inline void* Start = Memory::GetRVAPointer<void>(19850928); } /* void LevelController__Start (LevelController_o* __this, const MethodInfo* method); */
        namespace GameController { inline void* Exit = Memory::GetRVAPointer<void>(16680496); } /* void GameController__Exit (GameController_o* __this, const MethodInfo* method); */
        namespace PauseMenuController { inline void* Leave = Memory::GetRVAPointer<void>(24596128); } /* void PauseMenuController__Leave (PauseMenuController_o* __this, const MethodInfo* method); */
        namespace RewardManager { inline void* Awake = Memory::GetRVAPointer<void>(29297376); } /* void RewardManager__Awake (RewardManager_o* __this, const MethodInfo* method); */
        namespace Player { inline void* Update = Memory::GetRVAPointer<void>(23864624); } /* void Player__Update (Player_o* __this, const MethodInfo* method); */

        namespace SceneManager {

            inline void* LoadScene = Memory::GetRVAPointer<void>(11412016); /* void UnityEngine_SceneManagement_SceneManager__LoadScene (System_String_o* sceneName, const MethodInfo* method); */
            inline void* SceneLoaded = Memory::GetRVAPointer<void>(11410112); /* void UnityEngine_SceneManagement_SceneManager__Internal_SceneLoaded (UnityEngine_SceneManagement_Scene_o scene, int32_t mode, const MethodInfo* method); */

        }

        namespace FuseBox {

            inline void* Use = Memory::GetRVAPointer<void>(32331200); /* void FuseBox__Use (FuseBox_o* __this, const MethodInfo* method); */
            inline void* TurnOff = Memory::GetRVAPointer<void>(32296176); /* void FuseBox__TurnOff (FuseBox_o* __this, bool ___________, const MethodInfo* method); */

        }

    }

}
