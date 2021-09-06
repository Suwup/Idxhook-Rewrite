#include "ihpch.h"

#include "Idxhook/Core/Cheat.h"	

#include <thread>

static void Init()
{
	AllocConsole();
	FILE* f = nullptr;
	freopen_s(&f, "CONOUT$", "w", stdout);

	auto cheat = new Idxhook::Cheat();
	cheat->Run();
}

int __stdcall DllMain(void* dllHandle, unsigned long reason, void* reserved)
{
	if (reason != DLL_PROCESS_ATTACH)
		return false;

	DisableThreadLibraryCalls(static_cast<HMODULE>(dllHandle));

	std::thread(Init).detach();
	return true;
}
