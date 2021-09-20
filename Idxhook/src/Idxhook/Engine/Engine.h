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

		enum class RpcTarget : int32_t
		{
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
			Member(float, float3, 0x48);
			Member(float, float4, 0x4C);
			Member(float, float5, 0x50);
		};
    };

	struct CharacterController
	{
		bool SimpleMove(const UnityEngine::Vector3& speed) { return Memory::CallFunction<bool, void*, UnityEngine::Vector3>(Offsets::Methods::CharacterController::SimpleMove, this, speed); }
		UnityEngine::Vector3 GetVelocity() { return Memory::CallFunction<UnityEngine::Vector3, void*>(Offsets::Methods::CharacterController::get_velocity, this); }
	};

	struct Player : public UnityEngine::Component
	{
        union
		{
            Member(PhotonView*, Photon, 0x18);
            Member(bool, IsDead, 0x20);
            Member(PlayerSanity*, Sanity, 0xB0);
            Member(PlayerStamina*, Stamina, 0xE0);
            Member(CharacterController*, CharController, 0xE8);
            Member(FirstPersonController*, FirstPersonController, 0xF8);
            Member(PCPropGrab*, GrabProp, 0x100);
            Member(UnityEngine::Animator*, Animator, 0x140);
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
            Member(GhostEventPlayer*, EventPlayer, 0x58);
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

	struct Renderer : public UnityEngine::Component
	{
		bool GetEnabled() { return Memory::CallFunction<bool, void*>(Offsets::Methods::Renderer::get_enabled, this); }
		void SetEnabled(bool value) { return Memory::CallFunction<void, void*, bool>(Offsets::Methods::Renderer::set_enabled, this, value); }
	};

	struct GhostAI : public UnityEngine::Component
	{
		enum class States : int32_t
		{
			idle = 0,
			wander = 1,
			hunting = 2,
			favouriteRoom = 3,
			light = 4,
			door = 5,
			throwing = 6,
			fusebox = 7,
			appear = 8,
			doorKnock = 9,
			windowKnock = 10,
			carAlarm = 11,
			radio = 12,
			flicker = 13,
			lockDoor = 14,
			cctv = 15,
			randomEvent = 16,
			GhostAbility = 17,
			killPlayer = 18,
			sink = 19,
			sound = 20,
			painting = 21,
			mannequin = 22,
			teleportObject = 23,
			animationObject = 24
		};

        union
		{
            Member(UnityEngine::Animator*, Animator, 0x30);
            Member(GhostInfo*, Info, 0x38);
            Member(GhostActivity*, Activity, 0x58);
			Member(System::Array<Renderer>*, RendererArray, 0x68);
            Member(bool, IsHunting, 0xA8);
			Member(Player*, PlayerToKill, 0xC0);
        };

        void Appear() { return Memory::CallFunction<void, void*, bool>(Offsets::Methods::GhostAI::Appear, this, true); }
        void RandomEvent() { return Memory::CallFunction<void, void*>(Offsets::Methods::GhostAI::RandomEvent, this); }
        void ChangeState(States state, struct PhotonObjectInteract* object, System::Array<struct PhotonObjectInteract>* objectArray) { return Memory::CallFunction<void, void*, States, struct PhotonObjectInteract*, System::Array<struct PhotonObjectInteract>*>(Offsets::Methods::GhostAI::ChangeState, this, state, object, objectArray); }
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
