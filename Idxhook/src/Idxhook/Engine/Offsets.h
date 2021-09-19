#pragma once

namespace Idxhook::Offsets {

    namespace Methods {

        namespace Screen {

			inline uintptr_t get_width = 0;
			inline uintptr_t get_height = 0;

        }

		namespace Renderer {

			inline uintptr_t get_enabled = 0;
			inline uintptr_t set_enabled = 0;

		}

        namespace Camera {

            inline uintptr_t get_main = 0;
            inline uintptr_t get_fieldOfView = 0;
            inline uintptr_t set_fieldOfView = 0;
            inline uintptr_t WorldToScreenPoint = 0;

        }

        namespace Component { inline uintptr_t get_transform = 0; }

        namespace Transform {

			inline uintptr_t get_position = 0;
			inline uintptr_t set_position = 0;
			inline uintptr_t TransformDirection = 0;
			inline uintptr_t TransformPoint = 0;

        }

        namespace Vector3 {

			inline uintptr_t Distance = 0;
			inline uintptr_t Magnitude = 0;
			inline uintptr_t op_Addition = 0;

        }

		namespace CharacterController {

			inline uintptr_t SimpleMove = 0;
			inline uintptr_t get_velocity = 0;

		}

		namespace Text { inline uintptr_t get_text = 0; }
		namespace Scene { inline uintptr_t GetBuildIndexInternal = 0; }

		namespace Animator {

			inline uintptr_t GetFloat = 0;
			inline uintptr_t SetFloat = 0;
			inline uintptr_t GetBool = 0;
			inline uintptr_t SetBool = 0;
			inline uintptr_t GetInteger = 0;
			inline uintptr_t SetInteger = 0;
			inline uintptr_t GetBoneTransform = 0;

		}

		namespace Rigidbody { inline uintptr_t set_mass = 0; }

		namespace PhotonNetwork
		{
			inline uintptr_t set_NickName = 0;
			inline uintptr_t get_IsMasterClient = 0;
		}

		namespace PhotonView { inline uintptr_t RPC = 0; }
		namespace Marshal { inline uintptr_t PtrToStringAnsi = 0; }
		namespace Mission { inline uintptr_t Completed = 0; }

        namespace GhostAI {

			inline uintptr_t Appear = 0;
			inline uintptr_t RandomEvent = 0;

        }

        namespace GhostActivity {

			inline uintptr_t Interact = 0;
			inline uintptr_t InteractWithARandomDoor = 0;

        }
    }

    namespace TypeInfo {

		inline uintptr_t GameController = 0;
		inline uintptr_t EvidenceController = 0;
		inline uintptr_t MissionManager = 0;
		inline uintptr_t GhostController = 0;

    }

    namespace Hooks {

        namespace GUIUtility { inline void* CheckOnGUI = nullptr; }
        namespace GhostAI { inline void* Start = nullptr; }
        namespace DNAEvidence { inline void* Start = nullptr; }
        namespace LevelController { inline void* Start = nullptr; }
        namespace GameController { inline void* Exit = nullptr; }
        namespace PauseMenuController { inline void* Leave = nullptr; }
        namespace RewardManager { inline void* Awake = nullptr; }
        namespace Player { inline void* Update = nullptr; }

        namespace SceneManager {

            inline void* LoadScene = nullptr;
            inline void* Internal_SceneLoaded = nullptr;

        }

        namespace FuseBox {

			inline void* TurnOff = nullptr;
            inline void* Use = nullptr;

        }

    }

}
