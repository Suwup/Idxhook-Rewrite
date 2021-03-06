#include "ihpch.h"
#include "ImGuiLayer.h"

#include "Idxhook/Core/Cheat.h"
#include "Idxhook/Engine/GameState.h"
#include "Idxhook/Engine/Other.h"
#include "Idxhook/Engine/Il2cpp.h"

#include <imgui_internal.h>
#include <iostream>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Idxhook {

#define BIND_KEY_FN(key, fn) if (LOWORD(wParam) == key) s_Instance->fn = !s_Instance->fn;

	ImGuiLayer* ImGuiLayer::s_Instance = nullptr;

	ImGuiLayer::ImGuiLayer()
	{
		s_Instance = this;
	}

	LRESULT __stdcall ImGuiLayer::WndProcHook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_KEYDOWN)
		{
			BIND_KEY_FN(VK_INSERT, m_MenuOpen);
		}

		if (!s_Instance->m_Initialized)
			return CallWindowProcW(s_Instance->m_WndProc, hwnd, msg, wParam, lParam);

		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
			return true;

		return CallWindowProcW(s_Instance->m_WndProc, hwnd, msg, wParam, lParam);
	}

	HRESULT __stdcall ImGuiLayer::PresentHook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
	{
		std::call_once(s_Instance->m_Init, [&SwapChain]()
		{
			s_Instance->OnInit(SwapChain);
			s_Instance->m_Initialized = true;
		});

		do
		{
			s_Instance->Begin();
			{
				static const ImColor color = ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f });

				do
				{
					ImGui::SetWindowPos({}, ImGuiCond_Always);
					ImGui::SetWindowSize(*(const ImVec2*)&Cheat::ScreenSize(), ImGuiCond_Always);

					const auto drawList = ImGui::GetBackgroundDrawList();

					drawList->AddText(nullptr, 0.0f, { 10.0f, 10.0f }, ImGui::GetColorU32(IM_COL32_WHITE), "Idxhook [Unmaintained]");

					if (Cheat::Credits())
					{
						drawList->AddText(nullptr, 0.0f, { 10.0f, 50.0f }, ImGui::GetColorU32(IM_COL32_WHITE), "Credits:");
						drawList->AddText(nullptr, 0.0f, { 10.0f, 90.0f }, ImGui::GetColorU32(IM_COL32_WHITE), "Suwup");
						drawList->AddText(nullptr, 0.0f, { 10.0f, 110.0f }, ImGui::GetColorU32(IM_COL32_WHITE), "Galxiez");
						drawList->AddText(nullptr, 0.0f, { 10.0f, 130.0f }, ImGui::GetColorU32(IM_COL32_WHITE), "Darkest Euphoria");
						drawList->AddText(nullptr, 0.0f, { 10.0f, 150.0f }, ImGui::GetColorU32(IM_COL32_WHITE), "Lanylow");
					}

					for (size_t i = 1; i <= Cheat::MissionSize(); i++)
					{
						const MissionParams& mission = Cheat::Missions()[i - 1];
						if (!mission.Name.c_str())
							break;

						drawList->AddText(nullptr, 0.0f, { 10.0f, 250.0f + i * 20.0f }, ImGui::GetColorU32({ 1.0f, 1.0f, 0.0f, 1.0f }), mission.Name.c_str());
					}

					if (Cheat::GhostEnable())
					{
						if (Cheat::GhostSkeletonEnable())
						{
							for (const auto& it : Cheat::GhostBones())
							{
								if (!it.Valid) break;
								drawList->AddLine(*(const ImVec2*)&it.A, *(const ImVec2*)&it.B, color);
							}
						}

						if (Cheat::GhostBoxEnable())
						{
							auto& box = Cheat::GhostBox();
							if (box.Valid)
							{
								for (size_t i = 0; i < 4; i++)
								{
									drawList->AddLine(*(const ImVec2*)&box.Location[0][i], *(const ImVec2*)&box.Location[0][(i + 1) % 4], color, false);
									drawList->AddLine(*(const ImVec2*)&box.Location[1][i], *(const ImVec2*)&box.Location[1][(i + 1) % 4], color, false);
									drawList->AddLine(*(const ImVec2*)&box.Location[0][i], *(const ImVec2*)&box.Location[1][i], color, false);
								}
							}
						}
					}

					if (Cheat::PlayersEnable())
					{
						if (Cheat::PlayersSkeletonEnable())
						{
							for (const auto& player : Cheat::PlayerBones())
							{
								if (player.empty())
									continue;

								for (const auto& it : player)
								{
									if (!it.Valid) break;
									drawList->AddLine(*(const ImVec2*)&it.A, *(const ImVec2*)&it.B, color);
								}
							}
						}
					}

					if (Cheat::ItemEnable())
					{
						for (auto& it : Cheat::Items())
						{
							if (it.Name && it.Valid)
							{
								auto size = ImGui::CalcTextSize(it.Name);
								ImVec2& screen = *(ImVec2*)&it.Location;
								screen.x -= size.x * 0.5f;
								screen.y -= size.y;

								drawList->AddText(nullptr, 0.0f, { screen.x - 1.0f, screen.y + 1.0f }, ImGui::GetColorU32(IM_COL32_BLACK), it.Name);
								drawList->AddText(nullptr, 0.0f, screen, color, it.Name);
							}
						}
					}
				} while (false);

				do
				{
					if (!s_Instance->m_MenuOpen)
						break;
					
					ImGui::SetNextWindowSize({ 650.0f, 350.0f });
					ImGui::Begin("Idxhook", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
					ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_NoTabListScrollingButtons);
					{
						if (ImGui::BeginTabItem("General"))
						{
							ImGui::Checkbox("Credits", &Cheat::Credits());
							ImGui::Separator();

							ImGui::Checkbox("xQc speed", &Cheat::xQcSpeed());
							ImGui::SliderFloat("xQc speed multiplier", &Cheat::xQcSpeedMultiplier(), 0.1f, 2.0f, "%.2f");

							ImGui::Spacing();

							ImGui::Checkbox("Max stamina", &Cheat::MaxStamina());
							ImGui::Checkbox("Max sanity", &Cheat::MaxSanity());
							ImGui::Checkbox("Max lights", &Cheat::MaxLights());

							ImGui::Spacing();

							float& fov = Cheat::FieldOfView();
							if (ImGui::SliderFloat("Field Of View (retarded)", &fov, 20.0f, 180.0f, "%.2f"))
							{
								if (GameState::Pointers::CheckPointers())
									UnityEngine::Camera::GetMain()->SetFieldOfView(fov);
							}

							ImGui::EndTabItem();
						}

						if (ImGui::BeginTabItem("Item"))
						{
							ImGui::Checkbox("Enable", &Cheat::ItemEnable());

							ImGui::ColorEdit4("Color", (float*)&color);

							ImGui::EndTabItem();
						}

						if (ImGui::BeginTabItem("Ghost"))
						{
							ImGui::Checkbox("Enable", &Cheat::GhostEnable());

							ImGui::Checkbox("Skeleton", &Cheat::GhostSkeletonEnable());
							ImGui::Checkbox("Box", &Cheat::GhostBoxEnable());
							ImGui::Checkbox("Render model", &Cheat::GhostRenderModel());

							ImGui::ColorEdit4("Color", (float*)&color);
							ImGui::Spacing();

							ImGui::EndTabItem();
						}

						if (ImGui::BeginTabItem("Ghost Info"))
						{
							const GhostInfoParams& info = Cheat::GhostInfo();

							ImGui::Text("Name: %s", info.Name.c_str());
							ImGui::Text("Age: %s", info.Age.c_str());
							ImGui::Text("Room: %s", info.Room.c_str());
							ImGui::Text("Type: %s", info.Type.c_str());
							ImGui::Text("Evidence: %s", info.Evidence.c_str());
							ImGui::Text("Gender: %s", info.Gender.c_str());
							ImGui::Text("Hunting: %s", info.Hunting.c_str());

							ImGui::EndTabItem();
						}

						if (ImGui::BeginTabItem("Evidence"))
						{
							for (size_t i = 0; i < Cheat::MissionSize(); i++)
							{
								auto& mission = Cheat::Missions()[i];

								ImGui::Text(mission.Name.c_str());

								if (!mission.IsCompleted)
								{
									ImGui::SameLine();
									if (ImGui::Button(std::string("Complete##" + std::to_string(i)).c_str()))
										mission.ShouldComplete = true;
								}
							}

							if (ImGui::Button("Complete all missions"))
								Cheat::CompleteAllMissions() = true;

							ImGui::EndTabItem();
						}

						if (ImGui::BeginTabItem("Players"))
						{
							ImGui::Checkbox("Enable", &Cheat::PlayersEnable());

							ImGui::Checkbox("Skeleton", &Cheat::PlayersSkeletonEnable());
							ImGui::Checkbox("Name", &Cheat::PlayersNameEnable());

							ImGui::ColorEdit4("Color", (float*)&color);

							ImGui::EndTabItem();
						}

						if (GameState::Pointers::CheckPointers())
						{
							if (ImGui::BeginTabItem("Player List"))
							{
								auto playerList = (*(Engine::GameController**)Offsets::TypeInfo::GameController->static_fields)->PlayerList;
								for (size_t i = 0; i < playerList->Size; i++)
								{
									auto data = playerList->Items->Values[i];
									auto player = data->RealPlayer;

									std::string playerName = std::wstring_convert<std::codecvt_utf8_utf16<uint16_t>, uint16_t>{}.to_bytes(data->PlayerName->Chars);

									ImGui::NewLine();
									ImGui::Text(std::string(playerName + " -> " + (player->IsDead ? "Dead" : "Alive")).c_str());
#if KILL_PLAYER_NOT_WORKING
									ImGui::SameLine();

									if (PhotonNetwork::IsMasterClient())
									{
										if (ImGui::Button(std::string("Kill##" + playerName).c_str()))
										{
											Engine::GhostAI* ghost = ((Engine::LevelController*)GameState::Pointers::LevelController)->CurrentGhost;
											ghost->PlayerToKill = player;
											ghost->ChangeState(Engine::GhostAI::States::summoningCircle, nullptr, nullptr);
											player->GetTransform()->SetPosition(ghost->GetTransform()->GetPosition());
											//player->KillPlayer();
										}
									}
#endif
								}

								ImGui::EndTabItem();
							}
						}
					}
					ImGui::EndTabBar();
					ImGui::End();
				} while (false);
			}
			s_Instance->End();
		} while (false);

		return DirectX11::PresentOriginal(SwapChain, SyncInterval, Flags);
	}

	void ImGuiLayer::OnInit(IDXGISwapChain* swapChain)
	{
		if (!SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&m_Device)))
			return;

		m_Device->GetImmediateContext(&m_Context);

		DXGI_SWAP_CHAIN_DESC desc;
		swapChain->GetDesc(&desc);
		m_Window = desc.OutputWindow;

		ID3D11Texture2D* resource = nullptr;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&resource);

		if (resource)
		{
			m_Device->CreateRenderTargetView(resource, nullptr, &m_RenderTargetView);
			resource->Release();
		}

		// WndProc needed to handle ImGui Events
		m_WndProc = (WNDPROC)SetWindowLongPtr(m_Window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);

		// Setting up ImGui
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = nullptr;									// Since phasmophobia looks for "imgui.ini"
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.0f);

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight(); // Pure evil
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			style.WindowRounding = 0.0f;
			style.TabRounding = 0.0f;
			style.TabRounding = 0.0f;
			style.GrabRounding = 0.0f;
			style.ChildRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColors();

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(m_Window);
		ImGui_ImplDX11_Init(m_Device, m_Context);
	}

	void ImGuiLayer::OnShutdown()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		// Disable the garbage collector when we render so it does not get interrupted
		Il2cpp::Get().il2cpp_gc_disable();

		// Set up new frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::EndFrame();
		ImGui::Render();

		m_Context->OMSetRenderTargets(1, &m_RenderTargetView, 0);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Re-enable garbage collector
		Il2cpp::Get().il2cpp_gc_enable();
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		colors[ImGuiCol_WindowBg] = { 0.2f, 0.2f, 0.2f, 1.0f };
		colors[ImGuiCol_MenuBarBg] = { 0.149f, 0.149f, 0.149f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = { 0.5f, 0.5f, 0.5f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = { 0.5f, 0.5f, 0.5f, 1.0f };
		colors[ImGuiCol_HeaderActive] = { 0.5f, 0.5f, 0.5f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = { 0.3f, 0.3f, 0.3f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = { 0.42f, 0.42f, 0.42f, 1.0f };
		colors[ImGuiCol_ButtonActive] = { 0.3f, 0.3f, 0.3f, 1.0f };

		// Slider
		colors[ImGuiCol_SliderGrab] = { 0.16f, 0.16f, 0.16f, 1.0f };
		colors[ImGuiCol_SliderGrabActive] = { 0.16f, 0.16f, 0.16f, 1.0f };

		// Border
		colors[ImGuiCol_Border] = { 0.149f, 0.149f, 0.149f, 1.0f };
		colors[ImGuiCol_BorderShadow] = { 0.149f, 0.149f, 0.149f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = { 0.3f, 0.3f, 0.3f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = { 0.42f, 0.42f, 0.42f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = { 0.3f, 0.3f, 0.3f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = { 0.25f, 0.25f, 0.25f, 1.0f };
		colors[ImGuiCol_TabHovered] = { 0.3f, 0.3f, 0.3f, 1.0f };
		colors[ImGuiCol_TabActive] = { 0.25f, 0.25f, 0.25f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = { 0.25f, 0.25f, 0.25f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = { 0.25f, 0.25f, 0.25f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = { 0.149f, 0.149f, 0.149f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = { 0.149f, 0.149f, 0.149f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = { 0.149f, 0.149f, 0.149f, 1.0f };

		// Separator
		colors[ImGuiCol_Separator] = { 0.149f, 0.149f, 0.149f, 1.0f };
		colors[ImGuiCol_SeparatorHovered] = { 0.149f, 0.149f, 0.149f, 1.0f };
		colors[ImGuiCol_SeparatorActive] = { 0.149f, 0.149f, 0.149f, 1.0f };

		// Border
		style.FrameBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.WindowBorderSize = 1.0f;
	}

}
