#include "ihpch.h"
#include "Cheat.h"

#include "Idxhook/DirectX/DirectX11.h"
#include "Idxhook/ImGui/ImGuiLayer.h"

#include "Idxhook/Engine/GameState.h"
#include "Idxhook/Engine/System.h"
#include "Idxhook/Engine/Other.h"
#include "Idxhook/Engine/Il2cpp.h"

#include <minhook.h>
#include <iostream>

namespace Idxhook {

#define LOG_STATUS(msg, status) std::cout << msg " -> " << MH_StatusToString(status) << "\n"
#define BIND_FN_IMPL(msg, target, detour, original) LOG_STATUS(msg, MH_CreateHook(target, detour, original))
#define BIND_FN(loc, fn) BIND_FN_IMPL(#loc"::"#fn, Offsets::Hooks::loc::fn, reinterpret_cast<void*>(&Hooks::loc::fn), reinterpret_cast<void**>(&Original::loc::fn))

#define SET_TYPE_INFO(name, sig) Offsets::TypeInfo::##name = il2cpp->GetClass##sig;
#define SET_HOOK(namespaze, name, sig) Offsets::Hooks::##namespaze::name = il2cpp->GetMethod##sig;

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
		auto il2cpp = new Il2cpp();

		USE_TYPE_INFO(SET_TYPE_INFO);
		USE_HOOK(SET_HOOK);

		std::cout << "\nHooknig methods...\n\n";

		MH_Initialize();

		BIND_FN(DNAEvidence, Start);
		BIND_FN(GhostAI, Start);
		BIND_FN(LevelController, Start);
		BIND_FN(GameController, Exit);
		BIND_FN(PauseMenuController, Leave);
		BIND_FN(RewardManager, Awake);
		BIND_FN(SceneManager, LoadScene);
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

		std::cout << "\nHooked methods!\n\n";
	}

	void Cheat::Close()
	{
	}

	void Cheat::ChangeRenderState(bool value, bool shouldRender, System::Array<UnityEngine::Renderer>* renderers)
	{
		if (renderers && (value || shouldRender))
		{
			if (!value && shouldRender)
				shouldRender = false;
			else if (value && !shouldRender)
					shouldRender = true;

			for (uint64_t i = 0; i < renderers->MaxLength; i++)
			{
				auto renderer = renderers->Values[i];
				if (!renderer)
					continue;

				renderer->SetEnabled(value);
			}
		}
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

	static void Reset()
	{
		Cheat::GhostBones() = {};
		Cheat::PlayerBones() = {};
		Cheat::GhostBox() = {};
		Cheat::PlayerNames() = {};
		Cheat::GhostInfo() = {};
		Cheat::Missions() = {};
		Cheat::MissionSize() = 0;
		GameState::Pointers::ResetPointers();
	}

	void Cheat::Hooks::GameController::Exit(void* This, void* Info)
	{
		Reset();
		Original::GameController::Exit(This, Info);
	}

	void Cheat::Hooks::PauseMenuController::Leave(void* This, void* Info)
	{
		Reset();
		Original::PauseMenuController::Leave(This, Info);
	}

	void Cheat::Hooks::RewardManager::Awake(void* This, void* Info)
	{
		Reset();
		Original::RewardManager::Awake(This, Info);
	}

	void Cheat::Hooks::SceneManager::LoadScene(System::String* Name, void* Info)
	{
		Reset();
		Original::SceneManager::LoadScene(Name, Info);
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

		static auto ProjectWorldToScreen = [](UnityEngine::Camera* cam, const UnityEngine::Vector3& loc, UnityEngine::Vector2& screen, const UnityEngine::Vector2& size) -> bool
		{
			UnityEngine::Vector3 point = cam->WorldToScreenPoint(loc);

			if (point.Z < 0.0f)
				return false;

			UnityEngine::Vector2 screenLoc{ point.X, size.Y - point.Y };

			if (screenLoc.X > 0.0f && screenLoc.Y > 0.0f &&
				screenLoc.X < size.X && screenLoc.Y < size.Y)
			{
				screen = screenLoc;
				return true;
			}

			return false;
		};

		auto levelController = (Engine::LevelController*)GameState::Pointers::LevelController;
		auto evidenceController = *(Engine::EvidenceController**)Offsets::TypeInfo::EvidenceController->static_fields;
		auto gameController = *(Engine::GameController**)Offsets::TypeInfo::GameController->static_fields;

		{
			System::List<Engine::Mission>* missions = (*(Engine::MissionManager**)Offsets::TypeInfo::MissionManager->static_fields)->CurrentMissions;

			auto& completeAllMissions = CompleteAllMissions();

			for (size_t i = 0; i < missions->Size; i++)
			{
				Engine::Mission* mission = missions->Items->Values[i];

				auto& param = Missions()[i];
				if (completeAllMissions || param.ShouldComplete)
				{
					mission->IsCompleted = true;
					mission->Completed();
				}

				const char* isCompleted = mission->IsCompleted ? " (Completed)" : " (Not Completed)";

				param.Name = std::wstring_convert<std::codecvt_utf8_utf16<uint16_t>, uint16_t>{}.to_bytes(mission->Label->GetText()->Chars) + isCompleted;
				param.IsCompleted = mission->IsCompleted;
			}

			completeAllMissions = false;
			MissionSize() = missions->Size;
		}
#if 0
		if (config->BecomeGhost)
		{
			Engine::GhostAI* ghost = levelController->CurrentGhost;
			Engine::Player* localPlayer = gameController->MyPlayer->RealPlayer;

			if (!hasKilled)
			{
				ghost->PlayerToKill = localPlayer;
				ghost->ChangeState(Engine::GhostAI::States::killPlayer, nullptr, nullptr);
				hasKilled = true;
			}

			localPlayer->IsDead = false;
			ghost->canAttack = false;

			auto view = state->ghostAI->fields.view;
			if (!game::PhotonView_get_IsMine(view, nullptr))
				game::PhotonView_TransferOwnership(view, photonPlayer, nullptr);

			// Set the animator visible so that animations show
			auto anim = state->ghostAI->fields.anim;
			if (!game::Animator_GetBool(anim, fb::AnsiToString("isVisible"), nullptr))
				game::Animator_SetBool(anim, fb::AnsiToString("isVisible"), true, nullptr);
			if (game::Animator_GetFloat(anim, fb::AnsiToString("speed"), nullptr) != localMagnitude)
				game::Animator_SetFloat(anim, fb::AnsiToString("speed"), localMagnitude, nullptr);

			auto& desiredMove = localPlayer->fields.firstPersonController->fields.desiredMove;
			if (desiredMove.x != 0.0f || desiredMove.y != 0.0f)
			{
				if (game::Animator_GetBool(anim, fb::AnsiToString("isIdle"), nullptr))
				{
					game::Animator_SetBool(anim, fb::AnsiToString("isIdle"), false, nullptr);

					if (game::Animator_GetInteger(anim, fb::AnsiToString("WalkType"), nullptr) == 0)
						game::Animator_SetInteger(anim, fb::AnsiToString("WalkType"), 0, nullptr);
				}
			}
			else
			{
				if (!game::Animator_GetBool(anim, fb::AnsiToString("isIdle"), nullptr))
				{
					game::Animator_SetInteger(anim, fb::AnsiToString("IdleNumber"), std::rand() % 2, nullptr);
					game::Animator_SetBool(anim, fb::AnsiToString("isIdle"), true, nullptr);
				}
			}

			if (ImGui::IsKeyPressed(idx::Key::V))
			{
				Transform* ghost_t = game::Component_1_get_transform((Component_1*)state->ghostAI, nullptr);
				Vector3 ghost_p = game::Transform_get_position(ghost_t, nullptr);

				for (int i = 0; i < playerList->fields._size; i++)
				{
					auto data = playerList->fields._items->vector[i];
					auto player = data->fields.player;

					Transform* player_t = game::Component_1_get_transform((Component_1*)player, nullptr);
					Vector3 player_p = game::Transform_get_position(player_t, nullptr);

					if (player != localPlayer
						&& !player->fields.isDead
						&& game::Vector3_Distance(ghost_p,
							player_p, nullptr) < 1.0f)
					{
						state->ghostAI->fields.playerToKill = player;
						game::GhostAI_ChangeState(state->ghostAI, game::GhostAI_States__Enum::killPlayer, nullptr, nullptr, nullptr);
						break;
					}
	}
			}

			auto ghostTransform = game::Component_1_get_transform((Component_1*)state->ghostAI, nullptr);
			auto ghostPos = game::Transform_get_position(ghostTransform, nullptr);

			auto playerTransform = game::Component_1_get_transform((Component_1*)localPlayer, nullptr);
			auto playerPos = game::Transform_get_position(playerTransform, nullptr);
			auto playerRotation = game::Transform_get_rotation(playerTransform, nullptr);

			game::Transform_set_rotation(ghostTransform, playerRotation, nullptr);
			game::Transform_set_position(ghostTransform, game::Vector3_op_Subtraction(playerPos,
				{ 0, game::Transform_get_localScale(ghostTransform, nullptr).y / 2, 0 }, nullptr), nullptr);

			game::GhostAI_Appear(state->ghostAI, false, nullptr);
		}

			LocalPlayer->GrabProp->GrabDistance = (float)Menu::State::GrabDistance;


			System::List<Game::PhotonObjectInteract>* GrabObjectList = LocalPlayer->GrabProp->GrabObjectList;

			for (int ObjectIndex = 0; ObjectIndex < GrabObjectList->Size; ObjectIndex++) {
				Game::PhotonObjectInteract* Object = GrabObjectList->Items->Values[ObjectIndex];

				if (Object) {
					UnityEngine::Rigidbody* Rigidbody = Object->Rigidbody;


					if (Rigidbody)
						Rigidbody->SetMass((float)(51 - Menu::State::ThrowDistance) / 50.f);

				}
			}

			HandleButton(Menu::State::GhostSpawnDeadBody,
				{
				LocalPlayer->Photon->RPC(Marshal::PtrToStringAnsi((void*)"SpawnDeadBodyNetworked"), 0, nullptr);
				})
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

			for (int32_t i = 0; i < evidenceList->Size; i++)
			{
				Engine::Evidence* evidence = evidenceList->Items->Values[i];
				auto loc = evidence->GetTransform()->GetPosition();

				items[i].Valid = ProjectWorldToScreen(cam, loc, items[i].Location, screenSize);
				items[i].Name = evidenceTypes[evidence->Type];
			}

			{
				const int32_t index = evidenceList->Size;

				Engine::FuseBox* fuseBox = levelController->CurrentFuseBox;
				auto loc = fuseBox->GetTransform()->GetPosition();

				items[index].Valid = ProjectWorldToScreen(cam, loc, items[index].Location, screenSize);
				items[index].Name = "Fuse Box";
			}
		}

		if (GhostEnable())
		{
			Engine::GhostAI* ghost = levelController->CurrentGhost;
			Engine::GhostInfo* ghostInfo = ghost->Info;

			static const char* ghostNames[] =
			{
				"Spirit", "Wraith", "Phantom", "Poltergeist", "Banshee", "Jinn", "Mare", "Revenant", "Shade", "Demon",
				"Yurei", "Oni", "Yokai", "Hantu", "Goryo", "Myling", "Onryo", "TheTwins", "Raiju", "Obake", "Mimic"
			};

			static const char* ghostEvidences[] =
			{
				"None", "EMF", "SpiritBox", "Fingerprints", "Ghost Orb", "Ghost Writing Book", "Temperature","Dots Projector"
			};

			const char* isShy = ghostInfo->IsShy ? " (Shy)" : " (Not Shy)";

			GhostInfoParams& info = GhostInfo();
			info.Name = std::wstring_convert<std::codecvt_utf8_utf16<uint16_t>, uint16_t>{}.to_bytes(ghostInfo->Name->Chars) + isShy;
			info.Room = std::wstring_convert<std::codecvt_utf8_utf16<uint16_t>, uint16_t>{}.to_bytes(levelController->CurrentGhostRoom->RoomName->Chars);
			info.Age = std::to_string(ghostInfo->Age);
			info.Type = ghostNames[ghostInfo->Type];
			info.Evidence = ghostEvidences[ghostInfo->GhostEvidence];
			info.Gender = ghostInfo->IsMale ? "Male" : "Female";
			info.Hunting = ghost->IsHunting ? "Yes" : "No";

			ChangeRenderState(GhostRenderModel(), GhostShouldRenderModel(), ghost->RendererArray);

			if (GhostSkeletonEnable())
			{
				std::array<BoneParams, 18> bones{};
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

			if (GhostBoxEnable())
			{
				static UnityEngine::Vector3 extent{ 0.35f, 0.9f, 0.35f };
				static UnityEngine::Vector3 vertex[2][4]
				{
					-extent.X, -extent.Y, -extent.Z,
					 extent.X, -extent.Y, -extent.Z,
					 extent.X,  extent.Y, -extent.Z,
					-extent.X,  extent.Y, -extent.Z,
					-extent.X, -extent.Y,  extent.Z,
					 extent.X, -extent.Y,  extent.Z,
					 extent.X,  extent.Y,  extent.Z,
					-extent.X,  extent.Y,  extent.Z
				};

				auto& ghostBox = GhostBox();
				ghostBox.Valid = true;

				for (size_t k = 0; k < 2; k++)
				{
					for (size_t i = 0; i < 4; i++)
					{
						UnityEngine::Vector3 addition{ 0.0f, extent.Y, 0.0f };
						UnityEngine::Vector3 position{ vertex[k][i].Addition(addition) };
						UnityEngine::Vector3 point = ghost->GetTransform()->TransformPoint(position);

						UnityEngine::Vector2 screen{};
						if (!ProjectWorldToScreen(cam, point, screen, screenSize))
						{
							ghostBox.Valid = false;
							break;
						}

						ghostBox.Location[k][i] = screen;
					}
				}
			}

			if (PlayersEnable())
			{
				auto playerList = gameController->PlayerList;
				for (size_t i = 0; i < playerList->Size; i++)
				{
					auto data = playerList->Items->Values[i];
					if (!data || data == gameController->MyPlayer)
						continue;

					auto player = data->RealPlayer;
					if (!player)
						continue;

					if (PlayersSkeletonEnable())
					{
						std::array<BoneParams, 18> bones{};
						static const auto& bonesIDs = BoneIDArray();
						for (const auto& it : bonesIDs)
						{
							UnityEngine::Vector2 first{};
							UnityEngine::Vector2 second{};
							const size_t index = &it - &bonesIDs[0];

							bones[index] = ProjectWorldToScreen(cam, player->Animator->GetBoneTransform(it.first)->GetPosition(), first, screenSize)
								&& ProjectWorldToScreen(cam, player->Animator->GetBoneTransform(it.second)->GetPosition(), second, screenSize)
								? BoneParams{ true, first, second } : BoneParams{ false, {}, {} };
						}

						PlayerBones()[i] = bones;
					}

					if (PlayersNameEnable())
					{
						UnityEngine::Vector2 screen{};
						UnityEngine::Transform* transform = player->Animator->GetBoneTransform(UnityEngine::HumanBodyBones::Head);
						bool valid = ProjectWorldToScreen(cam, transform->GetPosition(), screen, screenSize);

						std::string name = std::wstring_convert<std::codecvt_utf8_utf16<uint16_t>, uint16_t>{}.to_bytes(data->PlayerName->Chars);
						PlayerNames()[i] = { valid, screen, name.c_str() };
					}
				}
			}
		}

		if (MaxLights())
			levelController->CurrentFuseBox->MaxLights = 50;
	}

	void Cheat::Hooks::Player::Update(Engine::Player* Player, void* Info)
	{
		Original::Player::Update(Player, Info);

		if (!GameState::Pointers::CheckPointers()) return;

		Engine::GameController* gameController = *(Engine::GameController**)Offsets::TypeInfo::GameController->static_fields;
		Engine::Player* localPlayer = gameController->MyPlayer->RealPlayer;

		if (localPlayer == Player)
		{
			if (xQcSpeed())
			{
				auto charController = localPlayer->CharController;
				if (!charController) return;

				auto& multiplier = xQcSpeedMultiplier();
				auto velocity = charController->GetVelocity();

				// TODO: Overload operator
				velocity.X *= multiplier;
				velocity.Y *= multiplier;
				velocity.Z *= multiplier;

				charController->SimpleMove(velocity);

				// Update the velocity since it changed when we moved the player
				localPlayer->Animator->SetFloat(Marshal::PtrToStringAnsi("speed"), charController->GetVelocity().Magnitude());
			}

			if (MaxStamina())
			{
				localPlayer->Stamina->float3 = 0.0f;
				localPlayer->Stamina->float4 = 3.0f;
				localPlayer->Stamina->float5 = 0.448327f;
			}

			if (MaxSanity())
				localPlayer->Sanity->Insanity = 0.0f;
		}
	}

}
