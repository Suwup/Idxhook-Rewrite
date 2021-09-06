#pragma once

#include "Idxhook/DirectX/DirectX11.h"

#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui_internal.h>

#include <mutex>

namespace Idxhook {

	class ImGuiLayer
	{
	public:

		ImGuiLayer();
		ImGuiLayer(const ImGuiLayer&) = delete;

		void OnInit(IDXGISwapChain* swapChain);
		void OnShutdown();

		void Begin();
		void End();

		void SetDarkThemeColors();

		static LRESULT __stdcall WndProcHook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static HRESULT __stdcall PresentHook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);

		static inline ImGuiLayer& Get() { return *s_Instance; }
	private:
		ImGuiWindow* Window = nullptr;
		ImVec2 Winsize = {};
		bool m_Initialized = false;
		bool m_MenuOpen = true;
		std::once_flag m_Init = {};
		WNDPROC m_WndProc = nullptr;
		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_Context = nullptr;
		ID3D11RenderTargetView* m_RenderTargetView = nullptr;
		HWND m_Window = nullptr;
	private:
		static ImGuiLayer* s_Instance;
	};

}

