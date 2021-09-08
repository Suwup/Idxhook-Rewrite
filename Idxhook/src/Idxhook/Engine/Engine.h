#pragma once
#include "UnityEngine.h"

namespace Idxhook::Engine {

	struct Evidence : public UnityEngine::Component
	{
        union
		{
            Member(int, Type, 0x34);
        };
    };

	struct EvidenceController
	{
        union
		{
            Member(System::List<Evidence>*, EvidenceList, 0x28);
        };
    };

	struct PhotonObjectInteract
	{
        union
		{
            Member(UnityEngine::Rigidbody*, Rigidbody, 0x160);
        };
    };

	struct PCPropGrab
	{
        union
		{
            Member(float, GrabDistance, 0x18);
            Member(System::List<PhotonObjectInteract>*, GrabObjectList, 0x60);
        };
    };

	struct FirstPersonController
	{
        union
		{
            Member(float, JumpSpeed, 0x20);
            Member(float, StickToGroundForce, 0x24);
            Member(float, GravityMultiplier, 0x28);
            Member(bool, Jump, 0x70);
        };
    };

	struct PlayerSanity
	{
        union
		{
            Member(float, Insanity, 0x28);
        };
    };

	namespace Photon::Pun {

		enum class RpcTarget : int
		{
			value__,
			All = 0,
			Others = 1,
			MasterClient = 2,
			AllBuffered = 3,
			OthersBuffered = 4,
			AllViaServer = 5,
			AllBufferedViaServer = 6
		};

	}

	struct PhotonView
	{
        void RPC(System::String* MethodName, Photon::Pun::RpcTarget Target, void* Arguments) { return Memory::CallFunction<void, void*, System::String*, Photon::Pun::RpcTarget, void*>(Offsets::Methods::PhotonView::RPC, this, MethodName, Target, Arguments); }
    };

	struct PlayerStamina
	{
		union
		{
			Member(float, fl3, 0x48);
			Member(float, fl4, 0x4C);
			Member(float, fl5, 0x50);
		};
    };

	struct Player : public UnityEngine::Component
	{
        union
		{
            Member(PhotonView*, Photon, 0x18);
            Member(bool, IsHunted, 0x20);
            Member(PlayerSanity*, Sanity, 0xA8);
            Member(PlayerStamina*, Stamina, 0xD0);
            Member(FirstPersonController*, FirstPersonController, 0xE8);
            Member(PCPropGrab*, GrabProp, 0xF0);
            Member(UnityEngine::Animator*, Animator, 0x130);
        };
    };

	namespace Photon::Realtime {

		struct Player
		{
			union
			{
				Member(int, ActorNumber, 0x18);
				Member(System::String*, NickName, 0x20);
			};
		};

	}

    struct PlayerData
	{
        union
		{
            Member(Player*, RealPlayer, 0x10);
            Member(Photon::Realtime::Player*, PhotonPlayer, 0x18);
            Member(System::String*, PlayerName, 0x20);
        };
    };

	struct GameController
	{
        union
		{
            Member(PlayerData*, MyPlayer, 0x18);
            Member(System::List<PlayerData>*, PlayerList, 0x58);
        };
    };

	struct GhostEventPlayer
	{
        union
		{
            Member(PhotonView*, Photon, 0x18);
        };
    };

	struct GhostController
	{
        union
		{
            Member(GhostEventPlayer*, EventPlayer, 0x60);
        };
    };

	struct GhostInfo
	{
        union
		{
            Member(int, Type, 0x20);
            Member(int, Age, 0x24);
            Member(bool, IsMale, 0x28);
            Member(System::String*, Name, 0x30);
            Member(bool, IsShy, 0x40);
        };
    };

	struct GhostActivity
	{
        void Interact() { return Memory::CallFunction<void, void*>(Offsets::Methods::GhostActivity::Interact, this); }
        void InteractWithARandomDoor() { return Memory::CallFunction<void, void*>(Offsets::Methods::GhostActivity::InteractWithARandomDoor, this); }
    };

	struct GhostAI : public UnityEngine::Component
	{
        union
		{
            Member(UnityEngine::Animator*, Animator, 0x30);
            Member(GhostInfo*, Info, 0x38);
            Member(GhostActivity*, Activity, 0x58);
            Member(bool, IsHunting, 0xA8);
        };

        void Appear() { return Memory::CallFunction<void, void*, bool>(Offsets::Methods::GhostAI::Appear, this, true); }
        void RandomEvent() { return Memory::CallFunction<void, void*>(Offsets::Methods::GhostAI::RandomEvent, this); }
    };

	struct FuseBox : public UnityEngine::Component
	{
        union
		{
            Member(int, MaxLights, 0x84);
        };
    };

	struct LevelRoom
	{
        union
		{
            Member(System::String*, RoomName, 0x50);
        };
    };

	struct SoundController
	{
        union
		{
            Member(PhotonView*, Photon, 0x18);
        };
    };

	struct Door
	{
        union
		{
            Member(PhotonView*, Photon, 0x60);
        };
    };

	struct LevelController
	{
        union
		{
            Member(LevelRoom*, CurrentPlayerRoom, 0x20);
            Member(LevelRoom*, CurrentGhostRoom, 0x28);
            Member(GhostAI*, CurrentGhost, 0x30);
            Member(System::Array<Door>*, DoorArray, 0x38);
            Member(FuseBox*, CurrentFuseBox, 0x60);
            Member(SoundController*, SoundController, 0x80);
        };
    };

	struct Mission
	{
        union
		{
            Member(bool, IsCompleted, 0x24);
            Member(UnityEngine::Text*, Label, 0x30);
        };

        void Completed() { return Memory::CallFunction<void, void*>(Offsets::Methods::Mission::Completed, this); }
    };

	struct MissionManager
	{
        union
		{
            Member(System::List<Mission>*, CurrentMissions, 0x50);
        };
    };
}