#include "ihpch.h"
#include "Cheat.h"

#include "Idxhook/DirectX/DirectX11.h"
#include "Idxhook/ImGui/ImGuiLayer.h"

#include "Idxhook/Engine/GameState.h"
#include "Idxhook/Engine/Offsets.h"

#include <minhook.h>
#include <iostream>

namespace Idxhook {

#define LOG_STATUS(msg, status) std::cout << msg " -> " << MH_StatusToString(status) << "\n"
#define BIND_FN_IMPL(msg, target, detour, original) LOG_STATUS(msg, MH_CreateHook(target, detour, original))
#define BIND_FN(loc, fn) BIND_FN_IMPL(#loc"::"#fn, Offsets::Hooks::loc::fn, reinterpret_cast<void*>(&Hooks::loc::fn), reinterpret_cast<void**>(&Original::loc::fn))

	Cheat* Cheat::s_Instance = nullptr;

	Cheat::Cheat()
	{
		s_Instance = this;
	}

	Cheat::~Cheat()
	{
	}

	void Cheat::Run()
	{
		MH_Initialize();

		BIND_FN(DNAEvidence, Start);
		BIND_FN(GhostAI, Start);
		BIND_FN(LevelController, Start);
		BIND_FN(GameController, Exit);
		BIND_FN(PauseMenuController, Leave);
		BIND_FN(RewardManager, Awake);
		BIND_FN(SceneManager, LoadScene);
		BIND_FN(SceneManager, SceneLoaded);
		BIND_FN(FuseBox, Use);
		BIND_FN(FuseBox, TurnOff);
		BIND_FN(GUIUtility, CheckOnGUI);
		BIND_FN(Player, Update);

		DirectX11::Init();

		auto imgui = new ImGuiLayer();
		auto hook = &imgui->PresentHook;
		auto original = reinterpret_cast<void**>(&DirectX11::PresentOriginal);

		BIND_FN_IMPL("DXGISwapChain::Present", DirectX11::PresentOriginal, hook, original);

		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Cheat::Close()
	{
	}

	void Cheat::Hooks::DNAEvidence::Start(void* This, void* Info)
	{
		Original::DNAEvidence::Start(This, Info);

		if (Utils::IsValid(This))
			GameState::Pointers::DNAEvidence = This;
	}

	void Cheat::Hooks::GhostAI::Start(void* This, void* Info)
	{
		Original::GhostAI::Start(This, Info);

		if (Utils::IsValid(This))
			GameState::Pointers::GhostAI = This;
	}

	void Cheat::Hooks::LevelController::Start(void* This, void* Info)
	{
		Original::LevelController::Start(This, Info);

		if (Utils::IsValid(This))
			GameState::Pointers::LevelController = This;
	}

	void Cheat::Hooks::GameController::Exit(void* This, void* Info)
	{
		GameState::Pointers::ResetPointers();
		Original::GameController::Exit(This, Info);
	}

	void Cheat::Hooks::PauseMenuController::Leave(void* This, void* Info)
	{
		GameState::Pointers::ResetPointers();
		Original::PauseMenuController::Leave(This, Info);
	}

	void Cheat::Hooks::RewardManager::Awake(void* This, void* Info)
	{
		GameState::Pointers::ResetPointers();
		Original::RewardManager::Awake(This, Info);
	}

	void Cheat::Hooks::SceneManager::LoadScene(System::String* Name, void* Info)
	{
		GameState::Pointers::ResetPointers();
		Original::SceneManager::LoadScene(Name, Info);
	}

	void Cheat::Hooks::SceneManager::SceneLoaded(UnityEngine::Scene Scene, int Mode, void* Info)
	{
		Original::SceneManager::SceneLoaded(Scene, Mode, Info);

		static const char* scenes[] =
		{
			"", "In Menu", "Tanglewood Street House", "Asylum", "Edgefield Street House",
			"Ridgeview Road House", "Brownstone High School", "Bleasdale Farmhouse",
			"Grafton Farmhouse", "Prison", "Willow Street House"
		};

		std::cout << "Loaded Scene: " << scenes[Scene.GetBuildIndexInternal()] << "\n";
	}

	void Cheat::Hooks::FuseBox::Use(void* This, void* Info)
	{
		if (!BlockFuseBox())
			Original::FuseBox::Use(This, Info);
	}

	void Cheat::Hooks::FuseBox::TurnOff(void* This, bool Unknown, void* Info)
	{
		if (!BlockFuseBox())
			Original::FuseBox::TurnOff(This, Unknown, Info);
	}

	static std::array<std::pair<UnityEngine::HumanBodyBones, UnityEngine::HumanBodyBones>, 16> Bones = { {
		{ UnityEngine::HumanBodyBones::Head, UnityEngine::HumanBodyBones::UpperChest },
		{ UnityEngine::HumanBodyBones::UpperChest, UnityEngine::HumanBodyBones::Hips  },
		{ UnityEngine::HumanBodyBones::Hips, UnityEngine::HumanBodyBones::LeftUpperLeg },
		{ UnityEngine::HumanBodyBones::Hips, UnityEngine::HumanBodyBones::RightUpperLeg },
		{ UnityEngine::HumanBodyBones::LeftUpperLeg, UnityEngine::HumanBodyBones::LeftLowerLeg },
		{ UnityEngine::HumanBodyBones::RightUpperLeg, UnityEngine::HumanBodyBones::RightLowerLeg },
		{ UnityEngine::HumanBodyBones::LeftLowerLeg, UnityEngine::HumanBodyBones::LeftFoot },
		{ UnityEngine::HumanBodyBones::RightLowerLeg, UnityEngine::HumanBodyBones::RightFoot },
		{ UnityEngine::HumanBodyBones::UpperChest, UnityEngine::HumanBodyBones::LeftShoulder },
		{ UnityEngine::HumanBodyBones::UpperChest, UnityEngine::HumanBodyBones::RightShoulder },
		{ UnityEngine::HumanBodyBones::LeftShoulder, UnityEngine::HumanBodyBones::LeftUpperArm },
		{ UnityEngine::HumanBodyBones::RightShoulder, UnityEngine::HumanBodyBones::RightUpperArm },
		{ UnityEngine::HumanBodyBones::LeftUpperArm, UnityEngine::HumanBodyBones::LeftLowerArm },
		{ UnityEngine::HumanBodyBones::RightUpperArm, UnityEngine::HumanBodyBones::RightLowerArm },
		{ UnityEngine::HumanBodyBones::LeftLowerArm, UnityEngine::HumanBodyBones::LeftHand },
		{ UnityEngine::HumanBodyBones::RightLowerArm, UnityEngine::HumanBodyBones::RightHand }
	} };

	void Cheat::Hooks::GUIUtility::CheckOnGUI(void* Info)
	{
		Original::GUIUtility::CheckOnGUI(Info);

		UnityEngine::Camera* cam = UnityEngine::Camera::GetMain();

		float& fov = FieldOfView();
		fov = cam->GetFieldOfView();
#if 0
		if (!GameState::Pointers::CheckPointers()) return;

		UnityEngine::Vector3 MainCameraPosition = MainCamera->GetTransform()->GetPosition();
		UnityEngine::Vector2 ScreenSizeVector = { (float)UnityEngine::Screen::GetWidth(), (float)UnityEngine::Screen::GetHeight() };

		static auto WorldToScreen = [](UnityEngine::Camera* Camera, UnityEngine::Vector3 Position, UnityEngine::Vector2& Output, UnityEngine::Vector2 ScreenSize) -> bool {
			UnityEngine::Vector3 Point = Camera->WorldToScreenPoint(Position);

			if (Point.Z < 0.f) return false;

			UnityEngine::Vector2 ScreenPosition = { Point.X, ScreenSize.Y - Point.Y };

			if (ScreenPosition.X > 0.f && ScreenPosition.Y > 0.f) {
				if (ScreenPosition.X < ScreenSize.X && ScreenPosition.Y < ScreenSize.Y) {
					Output.X = ScreenPosition.X;
					Output.Y = ScreenPosition.Y;

					return true;
				}
			}

			return false;
		};

		Game::LevelController* CurrentLevelController = ((Game::LevelController*)GameState::Pointers::LevelController);
		Game::GameController* CurrentGameController = (Utilities::GetTypeFromTypeInfo<Game::GameController>(Offsets::TypeInfo::GameController));
		Game::EvidenceController* CurrentEvidenceController = (Utilities::GetTypeFromTypeInfo<Game::EvidenceController>(Offsets::TypeInfo::EvidenceController));
		Game::MissionManager* CurrentMissionManager = (Utilities::GetTypeFromTypeInfo<Game::MissionManager>(Offsets::TypeInfo::MissionManager));
		Game::GhostController* CurrentGhostController = (Utilities::GetTypeFromTypeInfo<Game::GhostController>(Offsets::TypeInfo::GhostController));

		{
			System::List<Game::Mission>* MissionList = CurrentMissionManager->CurrentMissions;

			for (int MissionIndex = 0; MissionIndex < MissionList->Size; MissionIndex++)
			{
				Game::Mission* Mission = MissionList->Items->Values[MissionIndex];
#if 0
				if (MissionIndex > 0 && Menu::State::CompleteAllMissions)
				{
					Mission->IsCompleted = true;
					Mission->Completed();
				}
#endif
				struct Mission MissionObject;

				MissionObject.Label = System::Utilities::GetStringNative(Mission->Label->GetText());
				MissionObject.IsCompleted = Mission->IsCompleted;

				GameState::MissionData[MissionIndex] = MissionObject;
			}

			// Menu::State::CompleteAllMissions = false;

			GameState::MissionCount = MissionList->Size;
		}

		{
			Game::Player* LocalPlayer = CurrentGameController->LocalPlayer->RealPlayer;
			std::string LocalPlayerName = System::Utilities::GetStringNative(CurrentGameController->LocalPlayer->PlayerName);

			//RichPresence::SetUser(LocalPlayerName.c_str());

			GameState::LocalPlayerData::Sanity = std::to_string(100.f - LocalPlayer->Sanity->Insanity);
			GameState::LocalPlayerData::Hunted = LocalPlayer->IsHunted ? "Yes" : "No";
			GameState::LocalPlayerData::Room = System::Utilities::GetStringNative(CurrentLevelController->CurrentPlayerRoom->RoomName);

#if 0
			LocalPlayer->GrabProp->GrabDistance = (float)Menu::State::GrabDistance;
#endif

			System::List<Game::PhotonObjectInteract>* GrabObjectList = LocalPlayer->GrabProp->GrabObjectList;

			for (int ObjectIndex = 0; ObjectIndex < GrabObjectList->Size; ObjectIndex++) {
				Game::PhotonObjectInteract* Object = GrabObjectList->Items->Values[ObjectIndex];

				if (Object) {
					UnityEngine::Rigidbody* Rigidbody = Object->Rigidbody;

#if 0
					if (Rigidbody)
						Rigidbody->SetMass((float)(51 - Menu::State::ThrowDistance) / 50.f);
#endif
				}
			}

#if 0
			if (Menu::State::InfiniteStamina)
			{
				LocalPlayer->Stamina->fl3 = 0.f;
				LocalPlayer->Stamina->fl4 = 3.f;
				LocalPlayer->Stamina->fl5 = 0.448327f;
			}

			HandleButton(Menu::State::GhostSpawnDeadBody,
				{
				LocalPlayer->Photon->RPC(Marshal::PtrToStringAnsi((void*)"SpawnDeadBodyNetworked"), 0, nullptr);
				})
#endif
		}

		{
			System::List<Game::PlayerData>* PlayerList = CurrentGameController->PlayerList;

			for (int PlayerIndex = 0; PlayerIndex < PlayerList->Size; PlayerIndex++) {
				Game::PlayerData* PlayerInstance = PlayerList->Items->Values[PlayerIndex];

				UnityEngine::Vector3 PlayerPosition = PlayerInstance->RealPlayer->GetTransform()->GetPosition();

				Object PlayerObject;

				PlayerObject.WorldToScreen = WorldToScreen(MainCamera, PlayerPosition, PlayerObject.Position, ScreenSizeVector);
				PlayerObject.Distance = (int)UnityEngine::Vector3::Distance(MainCameraPosition, PlayerPosition);
				PlayerObject.Name = System::Utilities::GetStringNative(PlayerInstance->PlayerName);
				PlayerObject.BonesWorldToScreen = true;

				std::array<std::pair<UnityEngine::Vector2, UnityEngine::Vector2>, 16> BonesBuffer{};

				for (std::pair<UnityEngine::HumanBodyBones, UnityEngine::HumanBodyBones> BonePair : Bones)
				{
					UnityEngine::Vector2 First{ };
					UnityEngine::Vector2 Second{ };

					PlayerObject.BonesWorldToScreen &= WorldToScreen(MainCamera, PlayerInstance->RealPlayer->Animator->GetBoneTransform(BonePair.first)->GetPosition(), First, ScreenSizeVector);
					PlayerObject.BonesWorldToScreen &= WorldToScreen(MainCamera, PlayerInstance->RealPlayer->Animator->GetBoneTransform(BonePair.second)->GetPosition(), Second, ScreenSizeVector);

					size_t index = &BonePair - &Bones[0];
					BonesBuffer.at(index) = std::make_pair(First, Second);
				}

				PlayerObject.Bones = BonesBuffer;

				GameState::PlayerData[PlayerIndex] = PlayerObject;
			}

			GameState::PlayerCount = PlayerList->Size;
		}

		{
			static std::string EvidenceTypes[] = { "EMF Spot", "Ouija Board", "Fingerprint", "Footstep", "Bone", "Ghost", "Dead Body", "Dirty Water" };

			System::List<Game::Evidence>* EvidenceList = CurrentEvidenceController->EvidenceList;

			for (int EvidenceIndex = 0; EvidenceIndex < EvidenceList->Size; EvidenceIndex++) {
				Game::Evidence* Evidence = EvidenceList->Items->Values[EvidenceIndex];

				UnityEngine::Vector3 EvidencePosition = Evidence->GetTransform()->GetPosition();

				Object EvidenceObject;

				EvidenceObject.WorldToScreen = WorldToScreen(MainCamera, EvidencePosition, EvidenceObject.Position, ScreenSizeVector);
				EvidenceObject.Distance = (int)UnityEngine::Vector3::Distance(MainCameraPosition, EvidencePosition);
				EvidenceObject.Name = EvidenceTypes[Evidence->Type];

				GameState::EvidenceData[EvidenceIndex] = EvidenceObject;
			}

			GameState::EvidenceCount = EvidenceList->Size;
		}

#if 0
		{
			if (Menu::State::GhostLockSound || Menu::State::GhostUnlockSound) {
				System::Array<Game::Door>* DoorArray = CurrentLevelController->DoorArray;

				for (int DoorIndex = 0; DoorIndex < DoorArray->MaxLength; DoorIndex++) {
					Game::Door* Door = DoorArray->Values[DoorIndex];

					if (Door) {
						Game::PhotonView* DoorPhoton = Door->Photon;

						if (DoorPhoton) {
							if (Menu::State::GhostLockSound) {
								DoorPhoton->RPC(Marshal::PtrToStringAnsi((void*)"NetworkedPlayLockSound"), 0, nullptr);
								Menu::State::GhostLockSound = false;
							}

							if (Menu::State::GhostUnlockSound) {
								DoorPhoton->RPC(Marshal::PtrToStringAnsi((void*)"NetworkedPlayUnlockSound"), 0, nullptr);
								Menu::State::GhostUnlockSound = false;
							}
						}
					}
				}
			}
		}
#endif

		{
			Game::GhostAI* Ghost = CurrentLevelController->CurrentGhost;
			Game::GhostInfo* GhostInfo = Ghost->Info;

			static std::string GhostNames[] = { "None", "Spirit", "Wraith", "Phantom", "Poltergeist", "Banshee", "Jinn", "Mare",
												"Revenant", "Shade", "Demon", "Yurei", "Oni", "Yokai", "Hantu", "Goryo", "Myling" };

			static std::string GhostEvidences[] = { "None", "EMF Level 5, Spirit box, Ghost writing", "EMF Level 5, Spirit box, D.O.T.S Projector",
													"Spirit box, Fingerprints, D.O.T.S Projector", "Spirit box, Fingerprints, Ghost writing",
													"Ghost orbs, Fingerprints, D.O.T.S Projector", "EMF Level 5, Freezing temperatures, Fingerprints",
													"Ghost orbs, Spirit box, Ghost writing", "Ghost orbs, Freezing temperatures, Ghost writing",
													"EMF Level 5, Freezing temperatures, Ghost writing", "Freezing temperatures, Fingerprints, Ghost writing",
													"Ghost orbs, Freezing temperatures, D.O.T.S Projector", "EMF Level 5, Freezing temperatures, D.O.T.S Projector",
													"Ghost orbs, Spirit box, D.O.T.S Projector", "Ghost orbs, Freezing temperatures, Fingerprints",
													"EMF Level 5, Fingerprints, D.O.T.S Projector", "EMF Level 5, Fingerprints, Ghost writing" };

			GameState::GhostData::Name = System::Utilities::GetStringNative(GhostInfo->Name) + (GhostInfo->IsShy ? " (Shy)" : "");
			GameState::GhostData::Age = std::to_string(GhostInfo->Age);
			GameState::GhostData::Type = GhostNames[GhostInfo->Type];
			GameState::GhostData::Evidence = GhostEvidences[GhostInfo->Type];
			GameState::GhostData::Gender = GhostInfo->IsMale ? "Male" : "Female";
			GameState::GhostData::Room = System::Utilities::GetStringNative(CurrentLevelController->CurrentGhostRoom->RoomName);
			GameState::GhostData::Hunting = Ghost->IsHunting ? "Yes" : "No";

			UnityEngine::Vector3 GhostPosition = Ghost->GetTransform()->GetPosition();

			GameState::GhostData::Distance = (int)UnityEngine::Vector3::Distance(MainCameraPosition, GhostPosition);
			GameState::GhostData::WorldToScreen = WorldToScreen(MainCamera, GhostPosition, GameState::GhostData::Position, ScreenSizeVector);
			GameState::GhostData::BonesWorldToScreen = true;

			std::array<std::pair<UnityEngine::Vector2, UnityEngine::Vector2>, 16> BonesBuffer{ };

			for (std::pair<UnityEngine::HumanBodyBones, UnityEngine::HumanBodyBones> BonePair : Bones) {
				UnityEngine::Vector2 First{ };
				UnityEngine::Vector2 Second{ };

				GameState::GhostData::BonesWorldToScreen &= WorldToScreen(MainCamera, Ghost->Animator->GetBoneTransform(BonePair.first)->GetPosition(), First, ScreenSizeVector);
				GameState::GhostData::BonesWorldToScreen &= WorldToScreen(MainCamera, Ghost->Animator->GetBoneTransform(BonePair.second)->GetPosition(), Second, ScreenSizeVector);

				size_t index = &BonePair - &Bones[0];
				BonesBuffer.at(index) = std::make_pair(First, Second);
			}
#if 0
			HandleButton(Menu::State::GhostAppear, {
				Ghost->Appear();
				})

				HandleButton(Menu::State::GhostInteract, {
					Ghost->Activity->Interact();
					})

					HandleButton(Menu::State::GhostRandomEvent, {
						Ghost->RandomEvent();
						})

						HandleButton(Menu::State::GhostInteractWithDoor, {
							Ghost->Activity->InteractWithARandomDoor();
							})

							HandleButton(Menu::State::GhostEventSound, {
								CurrentGhostController->EventPlayer->Photon->RPC(Marshal::PtrToStringAnsi((void*)"PlaySoundNetworked"), 0, nullptr);
								})

								HandleButton(Menu::State::GhostKnockDoor, {
									CurrentLevelController->SoundController->Photon->RPC(Marshal::PtrToStringAnsi((void*)"PlayDoorKnockingSound"), 0, nullptr);
									})
#endif
				GameState::GhostData::Bones = BonesBuffer;
		}

		{
#if 0
			if (Menu::State::MaxLightsOverride) CurrentLevelController->CurrentFuseBox->MaxLights = 50;
#endif

			UnityEngine::Vector3 FuseBoxPosition = CurrentLevelController->CurrentFuseBox->GetTransform()->GetPosition();

			GameState::FuseBox.Distance = (int)UnityEngine::Vector3::Distance(MainCameraPosition, FuseBoxPosition);
			GameState::FuseBox.WorldToScreen = WorldToScreen(MainCamera, FuseBoxPosition, GameState::FuseBox.Position, ScreenSizeVector);
		}
#endif
	}

	void Cheat::Hooks::Player::Update(Engine::Player* Player, void* Info)
	{
		Original::Player::Update(Player, Info);

		if (!GameState::Pointers::CheckPointers()) return;

		Engine::GameController* gameController = Utils::GetTypeFromTypeInfo<Engine::GameController>(Offsets::TypeInfo::GameController);

		{
			Engine::Player* localPlayer = gameController->MyPlayer->RealPlayer;

			if (localPlayer == Player)
			{
#if 0
				if (Menu::State::Noclip)
				{
					Cheats::RunNoclip(localPlayer);
				}
				else
				{
					Cheats::ResetNoclip(localPlayer);
				}
#endif
			}
		}
	}

}
