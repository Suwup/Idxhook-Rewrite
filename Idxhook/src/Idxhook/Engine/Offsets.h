#pragma once

namespace Idxhook::Offsets {

    namespace Methods {

        namespace Screen {

            inline std::uintptr_t GetWidth = MemoryHelper::GetVA(11419568);
            inline std::uintptr_t GetHeight = MemoryHelper::GetVA(11419472);

        }

        namespace Camera {

            inline std::uintptr_t GetMain = MemoryHelper::GetVA(11186464);
            inline std::uintptr_t SetFieldOfView = MemoryHelper::GetVA(11189600);
            inline std::uintptr_t WorldToScreenPoint /* WorldToScreenPoint_1 */ = MemoryHelper::GetVA(11184672);

        }

        namespace Component /* Component_1 */ { inline std::uintptr_t GetTransform = MemoryHelper::GetVA(11198256); }

        namespace Transform {

			inline std::uintptr_t GetPosition = MemoryHelper::GetVA(11466480);
			inline std::uintptr_t SetPosition = MemoryHelper::GetVA(11468848);
			inline std::uintptr_t TransformDirection = MemoryHelper::GetVA(11463488);

        }

        namespace Vector3 {

			inline std::uintptr_t Distance = MemoryHelper::GetVA(14973456);
			inline std::uintptr_t Addition = MemoryHelper::GetVA(14982912);

        }

		namespace Text { inline std::uintptr_t GetText = MemoryHelper::GetVA(3075760); }
		namespace Scene { inline std::uintptr_t GetBuildIndexInternal = MemoryHelper::GetVA(11417520); }
		namespace Animator { inline std::uintptr_t GetBoneTransform = MemoryHelper::GetVA(15345280); }
		namespace Rigidbody { inline std::uintptr_t SetMass = MemoryHelper::GetVA(15292016); }
		namespace PhotonNetwork { inline std::uintptr_t SetNickName = MemoryHelper::GetVA(6455520); }
		namespace PhotonView { inline std::uintptr_t RPC = MemoryHelper::GetVA(44572640); }
		namespace Marshal { inline std::uintptr_t PtrToStringAnsi = MemoryHelper::GetVA(5066688); }
		namespace Time { inline std::uintptr_t GetDeltaTime = MemoryHelper::GetVA(11454080); }
		namespace Mission { inline std::uintptr_t Completed = MemoryHelper::GetVA(40947648); }

        namespace GhostAI {

			inline std::uintptr_t Appear = MemoryHelper::GetVA(25673952);
			inline std::uintptr_t RandomEvent = MemoryHelper::GetVA(25678560);

        }

        namespace GhostActivity {

			inline std::uintptr_t Interact = MemoryHelper::GetVA(25698496);
			inline std::uintptr_t InteractWithARandomDoor = MemoryHelper::GetVA(25696000);

        }
    }

    namespace TypeInfo {

		inline std::uintptr_t GameController = MemoryHelper::GetVA(56620912);
		inline std::uintptr_t EvidenceController = MemoryHelper::GetVA(56620352);
		inline std::uintptr_t MissionManager = MemoryHelper::GetVA(56618384);
		inline std::uintptr_t GhostController = MemoryHelper::GetVA(56615920);

    }

    namespace Hooks {

        namespace GUIUtility { inline void* CheckOnGUI = MemoryHelper::GetVAPointer<void>(0xE65420); }
        namespace GhostAI { inline void* Start = MemoryHelper::GetVAPointer<void>(0x187DB80); }
        namespace DNAEvidence { inline void* Start = MemoryHelper::GetVAPointer<void>(0x13E8700); }
        namespace LevelController { inline void* Start = MemoryHelper::GetVAPointer<void>(0x1A592A0); }
        namespace GameController { inline void* Exit = MemoryHelper::GetVAPointer<void>(0x11489F0); }
        namespace PauseMenuController { inline void* Leave = MemoryHelper::GetVAPointer<void>(0x1348660); }
        namespace RewardManager { inline void* Awake = MemoryHelper::GetVAPointer<void>(0x137CE50); }
        namespace Player { inline void* Update = MemoryHelper::GetVAPointer<void>(0x11FA490); }

        namespace SceneManager {

            inline void* LoadScene /* LoadScene_1 */ = MemoryHelper::GetVAPointer<void>(0xAE3230);
            inline void* SceneLoaded /* Internal_SceneLoaded */ = MemoryHelper::GetVAPointer<void>(0xAE2AC0);

        }

        namespace FuseBox {

            inline void* Use = MemoryHelper::GetVAPointer<void>(0x1148720);
            inline void* TurnOff = MemoryHelper::GetVAPointer<void>(0x1133AE0);

        }

    }

}
