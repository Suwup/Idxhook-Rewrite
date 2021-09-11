#pragma once

namespace Idxhook::Offsets {

#define OFFSET(name, offset) inline uintptr_t name = Memory::GetRVA(offset)
#define OFFSET_PTR(name, offset) inline void* name = Memory::GetRVAPointer<void>(offset)

    namespace Methods {

        namespace Screen {

			OFFSET(GetWidth, 0xb5a170);
			OFFSET(GetHeight, 0xb5a110);

        }

        namespace Camera {

            OFFSET(GetMain, 0xafe3d0);
            OFFSET(GetFieldOfView, 0xafe350);
            OFFSET(SetFieldOfView, 0xaff010);
            OFFSET(WorldToScreenPoint, 0xafdcd0);

        }

        namespace Component { OFFSET(GetTransform, 0xb011e0); }

        namespace Transform {

			OFFSET(GetPosition, 0xb658b0);
			OFFSET(SetPosition, 0xb661f0);
			OFFSET(TransformDirection, 0xb64d00);

        }

        namespace Vector3 {

			OFFSET(Magnitude, 0x103bc70);
			OFFSET(Distance, 0x103b8d0);
			OFFSET(Addition, 0x103ddc0);

        }

		namespace CharacterController {

			OFFSET(SimpleMove, 0x1080100);
			OFFSET(GetVelocity, 0x1080300);

		}

		namespace Text { OFFSET(GetText, 0x2eeeb0); }
		namespace Scene { OFFSET(GetBuildIndexInternal, 0xb59970); }

		namespace Animator {

			OFFSET(GetFloat, 0x1096720);
			OFFSET(SetFloat, 0x1096a60);
			OFFSET(GetBool, 0x1096630);
			OFFSET(SetBool, 0x1096a00);
			OFFSET(GetInteger, 0x1096770);
			OFFSET(SetInteger, 0x1096e40);
			OFFSET(GetBoneTransform, 0x1096540);

		}

		namespace Rigidbody { OFFSET(SetMass, 0x1089530); }

		namespace PhotonNetwork
		{
			OFFSET(SetNickName, 0x656020);
			OFFSET(IsMasterClient, 0x653c20);
		}

		namespace PhotonView { OFFSET(RPC, 0x2ac68f0); }
		namespace Marshal { OFFSET(PtrToStringAnsi, 0x502f00); }
		namespace Mission { OFFSET(Completed, 0x1f97400); }

        namespace GhostAI {

			OFFSET(Appear, 0x11e5280);
			OFFSET(RandomEvent, 0x11e6440);

        }

        namespace GhostActivity {

			OFFSET(Interact, 0x11eb250);
			OFFSET(InteractWithARandomDoor, 0x11ea890);

        }
    }

    namespace TypeInfo {

		OFFSET(GameController, 0x35ac680);
		OFFSET(EvidenceController, 0x35ac460);
		OFFSET(MissionManager, 0x35abcb8);
		OFFSET(GhostController, 0x35ab2d8);

    }

    namespace Hooks {

        namespace GUIUtility { OFFSET_PTR(CheckOnGUI, 0x10592e0); }
        namespace GhostAI { OFFSET_PTR(Start, 0x11e6b70); }
        namespace DNAEvidence { OFFSET_PTR(Start, 0x20cce20); }
        namespace LevelController { OFFSET_PTR(Start, 0x14e82a0); }
        namespace GameController { OFFSET_PTR(Exit, 0x11d4270); }
        namespace PauseMenuController { OFFSET_PTR(Leave, 0x18ac6a0); }
        namespace RewardManager { OFFSET_PTR(Awake, 0x1ce6910); }
        namespace Player { OFFSET_PTR(Update, 0x1793f30); }

        namespace SceneManager {

            OFFSET_PTR(LoadScene, 0xb593f0);
            OFFSET_PTR(SceneLoaded, 0xb58c80);

        }

        namespace FuseBox {

            OFFSET_PTR(Use, 0x2026c60);
            OFFSET_PTR(TurnOff, 0x201e390);

        }

    }

}
