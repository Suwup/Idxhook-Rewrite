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
			Member(System::List<Evidence>*, EvidenceList, 0x20);
		};
	};

	struct PhotonObjectInteract
	{
		union
		{
			Member(UnityEngine::Rigidbody*, Rigidbody, 0x168);
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
			Member(float, JumpSpeed, 0x20); // Lanylow where it at doe https://imgur.com/JEb1ZdD
			Member(float, StickToGroundForce, 0x20);
			Member(float, GravityMultiplier, 0x24);
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
		void RPC(System::String* MethodName, Photon::Pun::RpcTarget Target, void* Arguments) { CALL_METHOD(void, (void*, System::String*, Photon::Pun::RpcTarget, void*), (this, MethodName, Target, Arguments), ("PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3)); }
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

	struct Player : public UnityEngine::Component
	{
		union
		{
			Member(PhotonView*, Photon, 0x18);
			Member(bool, IsDead, 0x20);
			Member(PlayerSanity*, Sanity, 0xB8);
			Member(PlayerStamina*, Stamina, 0xE8);
			Member(UnityEngine::CharacterController*, CharController, 0xF0);
			Member(FirstPersonController*, FirstPersonController, 0x100);
			Member(PCPropGrab*, GrabProp, 0x108);
			Member(UnityEngine::Animator*, Animator, 0x148);
		};

		void KillPlayer() { CALL_METHOD(void, (void*), (this), ("Assembly-CSharp", "", "Player", "KillPlayer", 0)); }
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
			Member(System::List<PlayerData>*, PlayerList, 0x68);
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
			char UnknownData[0x20];

			Member(int, GhostEvidence, 0x8);
		};

		union
		{
			Member(int, Type, 0x4); // Seems to be the same as 0x0 ???????
			Member(int, Age, 0x10);
			Member(bool, IsMale, 0x14);
			Member(System::String*, Name, 0x18);
			Member(bool, IsShy, 0x28);
		};
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
			flicker = 12,
			cctv = 13,
			randomEvent = 14,
			GhostAbility = 15,
			mannequin = 16,
			teleportObject = 17,
			interact = 18,
			summoningCircle = 19,
			musicBox = 20
		};

		union
		{
			Member(States, State, 0x20);
			Member(UnityEngine::Animator*, Animator, 0x30);
			Member(GhostInfo*, Info, 0x38);
			Member(System::Array<UnityEngine::Renderer>*, RendererArray, 0x68);
			Member(bool, IsHunting, 0x9D);
			Member(Player*, PlayerToKill, 0xC0);
		};

		void Appear() { CALL_METHOD(void, (void*, bool), (this, true), ("Assembly-CSharp", "", "GhostAI", "Appear", 1)); }
		void RandomEvent() { CALL_METHOD(void, (void*), (this), ("Assembly-CSharp", "", "GhostAI", "RandomEvent", 0)); }
		void ChangeState(States state, PhotonObjectInteract* object, System::Array<PhotonObjectInteract>* objectArray, bool something = false) { CALL_METHOD(void, (void*, States, PhotonObjectInteract*, System::Array<PhotonObjectInteract>*, bool), (this, state, object, objectArray, something), ("Assembly-CSharp", "", "GhostAI", "ChangeState", 4)); }
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
			Member(System::String*, RoomName, 0x58);
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
			Member(PhotonView*, Photon, 0x68);
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
			Member(FuseBox*, CurrentFuseBox, 0x68);
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

		void Completed() { CALL_METHOD(void, (void*), (this), ("Assembly-CSharp", "", "Mission", "Completed", 0)); }
	};

	struct MissionManager
	{
		union
		{
			Member(System::List<Mission>*, CurrentMissions, 0x50);
		};
	};

}
