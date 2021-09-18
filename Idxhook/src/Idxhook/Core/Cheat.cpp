#include "ihpch.h"
#include "Cheat.h"

#include "Idxhook/DirectX/DirectX11.h"
#include "Idxhook/ImGui/ImGuiLayer.h"

#include "Idxhook/Engine/GameState.h"
#include "Idxhook/Engine/Offsets.h"
#include "Idxhook/Engine/System.h"
#include "Idxhook/Engine/Other.h"

#include <minhook.h>
#include <iostream>

namespace Idxhook {

#define LOG_STATUS(msg, status) std::cout << msg " -> " << MH_StatusToString(status) << "\n"
#define BIND_FN_IMPL(msg, target, detour, original) LOG_STATUS(msg, MH_CreateHook(target, detour, original))
#define BIND_FN(loc, fn) BIND_FN_IMPL(#loc"::"#fn, Offsets::Hooks::loc::fn, reinterpret_cast<void*>(&Hooks::loc::fn), reinterpret_cast<void**>(&Original::loc::fn))

#define LOG_OFFSET(name, offset) std::cout << #name" -> 0x" << std::hex << offset << "\n"
#define OFFSET_METHOD(name, str) LOG_OFFSET(name, (Offsets::Methods:: ## name = Memory::GetRVA(functionMap.find(str)->second)))
#define OFFSET_TYPE_INFO(name) LOG_OFFSET(name, (Offsets::TypeInfo:: ## name = Memory::GetRVA(typeInfoMap.find(#name"_c*")->second)))
#define OFFSET_HOOK(name, str) LOG_OFFSET(name, (Offsets::Hooks:: ## name = Memory::GetRVAPointer<void>(functionMap.find(str)->second)))

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
		// Maps containing our offsets set on entry point
		auto& functionMap = FunctionMap();
		auto& typeInfoMap = TypeInfoMap();

		// Methods
		{
			OFFSET_METHOD(Screen::get_width, "UnityEngine.Screen::get_width");
			OFFSET_METHOD(Screen::get_height, "UnityEngine.Screen::get_height");

			OFFSET_METHOD(Camera::get_main, "UnityEngine.Camera::get_main");
			OFFSET_METHOD(Camera::get_fieldOfView, "UnityEngine.Camera::get_fieldOfView");
			OFFSET_METHOD(Camera::set_fieldOfView, "UnityEngine.Camera::set_fieldOfView");
			OFFSET_METHOD(Camera::WorldToScreenPoint, "UnityEngine.Camera::WorldToScreenPoint");

			OFFSET_METHOD(Component::get_transform, "UnityEngine.Component::get_transform");

			OFFSET_METHOD(Transform::get_position, "UnityEngine.Transform::get_position");
			OFFSET_METHOD(Transform::set_position, "UnityEngine.Transform::set_position");
			OFFSET_METHOD(Transform::TransformDirection, "UnityEngine.Transform::TransformDirection");

			OFFSET_METHOD(Vector3::Distance, "UnityEngine.Vector3::Distance");
			OFFSET_METHOD(Vector3::Magnitude, "UnityEngine.Vector3::Magnitude");
			OFFSET_METHOD(Vector3::op_Addition, "UnityEngine.Vector3::op_Addition");

			OFFSET_METHOD(CharacterController::SimpleMove, "UnityEngine.CharacterController::SimpleMove");
			OFFSET_METHOD(CharacterController::get_velocity, "UnityEngine.CharacterController::get_velocity");

			OFFSET_METHOD(Text::get_text, "UnityEngine.UI.Text::get_text");

			OFFSET_METHOD(Scene::GetBuildIndexInternal, "UnityEngine.SceneManagement.Scene::GetBuildIndexInternal");

			OFFSET_METHOD(Animator::GetFloat, "UnityEngine.Animator::GetFloat");
			OFFSET_METHOD(Animator::SetFloat, "UnityEngine.Animator::SetFloat");
			OFFSET_METHOD(Animator::GetBool, "UnityEngine.Animator::GetBool");
			OFFSET_METHOD(Animator::SetBool, "UnityEngine.Animator::SetBool");
			OFFSET_METHOD(Animator::GetInteger, "UnityEngine.Animator::GetInteger");
			OFFSET_METHOD(Animator::SetInteger, "UnityEngine.Animator::SetInteger");
			OFFSET_METHOD(Animator::GetBoneTransform, "UnityEngine.Animator::GetBoneTransform");

			OFFSET_METHOD(Rigidbody::set_mass, "UnityEngine.Rigidbody::set_mass");

			OFFSET_METHOD(PhotonNetwork::set_NickName, "Photon.Pun.PhotonNetwork::set_NickName");
			OFFSET_METHOD(PhotonNetwork::get_IsMasterClient, "Photon.Pun.PhotonNetwork::get_IsMasterClient");

			OFFSET_METHOD(PhotonView::RPC, "Photon.Pun.PhotonView::RPC");

			OFFSET_METHOD(Marshal::PtrToStringAnsi, "System.Runtime.InteropServices.Marshal::PtrToStringAnsi");

			OFFSET_METHOD(Mission::Completed, "Mission::Completed");

			OFFSET_METHOD(GhostAI::Appear, "GhostAI::Appear");
			OFFSET_METHOD(GhostAI::RandomEvent, "GhostAI::RandomEvent");

			OFFSET_METHOD(GhostActivity::Interact, "GhostActivity::Interact");
			OFFSET_METHOD(GhostActivity::InteractWithARandomDoor, "GhostActivity::InteractWithARandomDoor");
		}

		// Type info
		{
			OFFSET_TYPE_INFO(GameController);
			OFFSET_TYPE_INFO(EvidenceController);
			OFFSET_TYPE_INFO(MissionManager);
			OFFSET_TYPE_INFO(GhostController);
		}

		// Hooked methods
		{
			OFFSET_HOOK(GUIUtility::CheckOnGUI, "UnityEngine.GUIUtility::CheckOnGUI");

			OFFSET_HOOK(GhostAI::Start, "GhostAI::Start");

			OFFSET_HOOK(DNAEvidence::Start, "DNAEvidence::Start");

			OFFSET_HOOK(LevelController::Start, "LevelController::Start");

			OFFSET_HOOK(GameController::Exit, "GameController::Exit");

			OFFSET_HOOK(PauseMenuController::Leave, "PauseMenuController::Leave");

			OFFSET_HOOK(RewardManager::Awake, "RewardManager::Awake");

			OFFSET_HOOK(Player::Update, "Player::Update");

			OFFSET_HOOK(SceneManager::LoadScene, "UnityEngine.SceneManagement.SceneManager::LoadScene");
			OFFSET_HOOK(SceneManager::Internal_SceneLoaded, "UnityEngine.SceneManagement.SceneManager::Internal_SceneLoaded");

			OFFSET_HOOK(FuseBox::TurnOff, "FuseBox::TurnOff");
			OFFSET_HOOK(FuseBox::Use, "FuseBox::Use");
		}

		MH_Initialize();

		BIND_FN(DNAEvidence, Start);
		BIND_FN(GhostAI, Start);
		BIND_FN(LevelController, Start);
		BIND_FN(GameController, Exit);
		BIND_FN(PauseMenuController, Leave);
		BIND_FN(RewardManager, Awake);
		BIND_FN(SceneManager, LoadScene);
		BIND_FN(SceneManager, Internal_SceneLoaded);
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

	void Cheat::Hooks::SceneManager::Internal_SceneLoaded(UnityEngine::Scene Scene, int Mode, void* Info)
	{
		Original::SceneManager::Internal_SceneLoaded(Scene, Mode, Info);

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

	void Cheat::Hooks::GUIUtility::CheckOnGUI(void* Info)
	{
		Original::GUIUtility::CheckOnGUI(Info);

		UnityEngine::Camera* cam = UnityEngine::Camera::GetMain();

		FieldOfView() = cam->GetFieldOfView();
		if (!GameState::Pointers::CheckPointers()) return;

		auto camLoc = cam->GetTransform()->GetPosition();
		auto& screenSize = ScreenSize();
		screenSize = { (float)UnityEngine::Screen::GetWidth(), (float)UnityEngine::Screen::GetHeight() };

		static auto ProjectWorldToScreen = [](UnityEngine::Camera* cam, const UnityEngine::Vector3& loc, UnityEngine::Vector2& screen, UnityEngine::Vector2 size) -> bool
		{
			UnityEngine::Vector3 Point = cam->WorldToScreenPoint(loc);

			if (Point.Z < 0.f)
				return false;

			UnityEngine::Vector2 screenLoc{ Point.X, size.Y - Point.Y };

			if (screenLoc.X > 0.f && screenLoc.Y > 0.f) {
				if (screenLoc.X < size.X && screenLoc.Y < size.Y)
				{
					screen.X = screenLoc.X;
					screen.Y = screenLoc.Y;

					return true;
				}
			}

			return false;
		};

		auto levelController = reinterpret_cast<Engine::LevelController*>(GameState::Pointers::LevelController);
		auto evidenceController = Utils::GetTypeFromTypeInfo<Engine::EvidenceController>(Offsets::TypeInfo::EvidenceController);

#if 0
		Engine::GameController* CurrentGameController = Utils::GetTypeFromTypeInfo<Engine::GameController>(Offsets::TypeInfo::GameController);
		Engine::EvidenceController* CurrentEvidenceController = Utils::GetTypeFromTypeInfo<Engine::EvidenceController>(Offsets::TypeInfo::EvidenceController);
		Engine::MissionManager* CurrentMissionManager = Utils::GetTypeFromTypeInfo<Engine::MissionManager>(Offsets::TypeInfo::MissionManager);
		Engine::GhostController* CurrentGhostController = Utils::GetTypeFromTypeInfo<Engine::GhostController>(Offsets::TypeInfo::GhostController);

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
		if (ItemEnable())
		{
			auto& items = Items();
			static const char* evidenceTypes[] = { "EMF Spot", "Ouija Board", "Fingerprint", "Footstep", "Bone", "Ghost", "Dead Body", "Dirty Water" };
			System::List<Engine::Evidence>* evidenceList = evidenceController->EvidenceList;

			for (int i = 0; i < evidenceList->Size; i++)
			{
				Engine::Evidence* evidence = evidenceList->Items->Values[i];

				auto loc = evidence->GetTransform()->GetPosition();

				items[i].Valid = ProjectWorldToScreen(cam, loc, items[i].Location, screenSize);
				items[i].Name = evidenceTypes[evidence->Type];
			}
		}

		if (GhostEnable())
		{
			Engine::GhostAI* ghost = levelController->CurrentGhost;
#if 0
			static std::string GhostNames[] =
			{
				"None", "Spirit", "Wraith", "Phantom", "Poltergeist", "Banshee", "Jinn", "Mare",
				"Revenant", "Shade", "Demon", "Yurei", "Oni", "Yokai", "Hantu", "Goryo", "Myling"
			};

			static std::string GhostEvidences[] =
			{
				"None", "EMF Level 5, Spirit box, Ghost writing", "EMF Level 5, Spirit box, D.O.T.S Projector",
				"Spirit box, Fingerprints, D.O.T.S Projector", "Spirit box, Fingerprints, Ghost writing",
				"Ghost orbs, Fingerprints, D.O.T.S Projector", "EMF Level 5, Freezing temperatures, Fingerprints",
				"Ghost orbs, Spirit box, Ghost writing", "Ghost orbs, Freezing temperatures, Ghost writing",
				"EMF Level 5, Freezing temperatures, Ghost writing", "Freezing temperatures, Fingerprints, Ghost writing",
				"Ghost orbs, Freezing temperatures, D.O.T.S Projector", "EMF Level 5, Freezing temperatures, D.O.T.S Projector",
				"Ghost orbs, Spirit box, D.O.T.S Projector", "Ghost orbs, Freezing temperatures, Fingerprints",
				"EMF Level 5, Fingerprints, D.O.T.S Projector", "EMF Level 5, Fingerprints, Ghost writing"
			};

			
			Engine::GhostInfo* ghostInfo = ghost->Info;

			GameState::GhostData::Name = System::Utilities::GetStringNative(ghostInfo->Name) + (ghostInfo->IsShy ? " (Shy)" : "");
			GameState::GhostData::Age = std::to_string(ghostInfo->Age);
			GameState::GhostData::Type = GhostNames[ghostInfo->Type];
			GameState::GhostData::Evidence = GhostEvidences[ghostInfo->Type];
			GameState::GhostData::Gender = ghostInfo->IsMale ? "Male" : "Female";
			GameState::GhostData::Room = System::Utilities::GetStringNative(CurrentLevelController->CurrentGhostRoom->RoomName);
			GameState::GhostData::Hunting = ghost->IsHunting ? "Yes" : "No";

			UnityEngine::Vector3 GhostPosition = ghost->GetTransform()->GetPosition();

			GameState::GhostData::Distance = (int)UnityEngine::Vector3::Distance(MainCameraPosition, GhostPosition);
			GameState::GhostData::WorldToScreen = WorldToScreen(MainCamera, GhostPosition, GameState::GhostData::Position, ScreenSizeVector);
			GameState::GhostData::BonesWorldToScreen = true;
#endif
			if (GhostSkeleton())
			{
				std::array<BoneParams, 16> bones{};
				static const auto& bonesIDs = BoneIDArray();
				for (const auto& it : bonesIDs)
				{
					UnityEngine::Vector2 first{};
					UnityEngine::Vector2 second{};
					const size_t index = &it - &bonesIDs[0];

					bones[index] = ProjectWorldToScreen(cam, ghost->Animator->GetBoneTransform(it.first)->GetPosition(), first, screenSize)
						&& ProjectWorldToScreen(cam, ghost->Animator->GetBoneTransform(it.second)->GetPosition(), second, screenSize)
						? BoneParams{ true, first, second } : BoneParams{ false, {}, {} };
				}

				GhostBones() = bones;
			}

			static UnityEngine::Vector3 extent{ 0.35f, 0.9f, 0.35f };
			static UnityEngine::Vector3 vertex[2][4]{};
			vertex[0][0] = { -extent.X, -extent.Y, -extent.Z };
			vertex[0][1] = {  extent.X, -extent.Y, -extent.Z };
			vertex[0][2] = {  extent.X,  extent.Y, -extent.Z };
			vertex[0][3] = { -extent.X,  extent.Y, -extent.Z };
			vertex[1][0] = { -extent.X, -extent.Y,  extent.Z };
			vertex[1][1] = {  extent.X, -extent.Y,  extent.Z };
			vertex[1][2] = {  extent.X,  extent.Y,  extent.Z };
			vertex[1][3] = { -extent.X,  extent.Y,  extent.Z };

			auto& ghostBox = GhostBox();
			ghostBox.Valid = true;

			for (size_t k = 0; k < 2; k++)
			{
				for (size_t i = 0; i < 4; i++)
				{
					UnityEngine::Vector3 addition{ 0.0f, extent.Y, 0.0f };
					UnityEngine::Vector3 transform = ghost->GetTransform()->TransformDirection(vertex[k][i].Addition(addition));
					//UnityEngine::Vector3 transform = ghostTransform->GetPosition();

					UnityEngine::Vector2 screen{};
					if (!ProjectWorldToScreen(cam, transform, screen, screenSize) ||
						screen.X > screenSize.X ||
						screen.Y > screenSize.Y)
					{
						ghostBox.Valid = false;
						break;
					}

					ghostBox.Location[k][i] = screen;
				}
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
		}
#if 0
		{
			if (Menu::State::MaxLightsOverride) CurrentLevelController->CurrentFuseBox->MaxLights = 50;

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
		Engine::Player* localPlayer = gameController->MyPlayer->RealPlayer;

		if (localPlayer == Player)
		{
			if (xQcSpeed())
			{
				auto charController = localPlayer->CharController;
				if (!charController) return;

				auto& multiplier = xQcSpeedMultiplier();
				auto velocity = charController->GetVelocity();

				velocity.X *= multiplier;
				velocity.Y *= multiplier;
				velocity.Z *= multiplier;

				charController->SimpleMove(velocity);

				// Update the velocity since it changed when we moved the player
				localPlayer->Animator->SetFloat(Marshal::PtrToStringAnsi("speed"), charController->GetVelocity().Magnitude());
			}

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
