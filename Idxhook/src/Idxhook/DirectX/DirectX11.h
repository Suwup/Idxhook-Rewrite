#pragma once
#include <stdint.h>
#include <dxgi.h>
#include <d3d11.h>

namespace Idxhook {

	class DirectX11
	{
	public:
		static HRESULT(__stdcall* PresentOriginal)(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);

	public:
		static void Init();
	};

}
