#include "ihpch.h"

#include "Idxhook/Core/Cheat.h"	

int __stdcall DllMain(void* dllHandle, unsigned long reason, void* reserved)
{
	if (reason != DLL_PROCESS_ATTACH)
		return false;

	DisableThreadLibraryCalls(static_cast<HMODULE>(dllHandle));

	auto cheat = new Idxhook::Cheat();

	cheat->Run();

	return true;
}
