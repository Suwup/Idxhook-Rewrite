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

int __stdcall DllMain(HMODULE lib, uint32_t reason, void*)
{
	if (reason != DLL_PROCESS_ATTACH)
		return false;

	DisableThreadLibraryCalls(lib);

	std::thread(Init).detach();
	return true;
}
