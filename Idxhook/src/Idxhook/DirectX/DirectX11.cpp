#include "ihpch.h"
#include "DirectX11.h"

namespace Idxhook {

	HRESULT(__stdcall* DirectX11::PresentOriginal)(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);

	void DirectX11::Init()
	{
		WNDCLASSEX windowClass =
		{
			sizeof(WNDCLASSEX),
			CS_HREDRAW | CS_VREDRAW,
			DefWindowProc,
			0,
			0,
			GetModuleHandle(nullptr),
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			L"BussySaka",
			nullptr
		};

		RegisterClassEx(&windowClass);
		auto window = CreateWindowW(windowClass.lpszClassName, L"Sussy Baka", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_11_0
		};

		DXGI_MODE_DESC bufferDesc =
		{
			100,
			100,
			{60, 1},
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
			DXGI_MODE_SCALING_UNSPECIFIED
		};

		DXGI_SWAP_CHAIN_DESC swapChainDesc =
		{
			bufferDesc,
			{1, 0},
			DXGI_USAGE_RENDER_TARGET_OUTPUT,
			1,
			window,
			1,
			DXGI_SWAP_EFFECT_DISCARD,
			DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
		};

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* context;

		auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context);

		if (FAILED(result))
		{
			DestroyWindow(window);
			UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return;
		}

		void** vmt = *(void***)swapChain;
		PresentOriginal = reinterpret_cast<decltype(PresentOriginal)>(vmt[8]);

		if (swapChain) { swapChain->Release(); swapChain = nullptr; }
		if (device) { device->Release(); device = nullptr; }
		if (context) { context->Release(); context = nullptr; }

		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
	}

}

