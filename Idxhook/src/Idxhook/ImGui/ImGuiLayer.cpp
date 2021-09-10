#include "ihpch.h"
#include "ImGuiLayer.h"

#include "Idxhook/Core/Cheat.h"
#include "Idxhook/Engine/GameState.h"

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
				do
				{
					ImGui::SetWindowPos({}, ImGuiCond_Always);
					ImGui::SetWindowSize(*(const ImVec2*)&Cheat::ScreenSize(), ImGuiCond_Always);

					{
						const auto drawList = ImGui::GetOverlayDrawList();
						static const ImColor color = ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f });

						for (const auto& it : Cheat::Bones())
						{
							if (!it.Valid) break;
							drawList->AddLine(*(const ImVec2*)&it.A, *(const ImVec2*)&it.B, color);
						}
					}
				} while (false);

				do
				{
					if (!s_Instance->m_MenuOpen) break;

					float& fov = Cheat::FieldOfView();

					ImGui::SetNextWindowSize({ 500.0f, 350.0f });
					ImGui::Begin("Idxhook");
					ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_NoTabListScrollingButtons);
					{
						if (ImGui::BeginTabItem("sussy baka"))
						{
							if (ImGui::SliderFloat("Field Of View", &fov, 20.0f, 180.0f, "%.2f"))
							{
								if (GameState::Pointers::CheckPointers())
									UnityEngine::Camera::GetMain()->SetFieldOfView(fov);
							}

							ImGui::EndTabItem();
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
		auto status = swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&m_Device);
		if (!SUCCEEDED(status))
			return;

		m_Device->GetImmediateContext(&m_Context);

		DXGI_SWAP_CHAIN_DESC desc;
		swapChain->GetDesc(&desc);
		m_Window = desc.OutputWindow;

		ID3D11Texture2D* resource = nullptr;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&resource);

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
		//il2cpp_gc_disable();

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
		//il2cpp_gc_enable();
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
