#include "ihpch.h"

#include "Idxhook/Core/Cheat.h"	

#include <thread>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <json.hpp>

static void Init()
{
	AllocConsole();
	FILE* f = nullptr;
	freopen_s(&f, "CONOUT$", "w", stdout);

	const std::string fileName = "offsets.json";
	if (!std::filesystem::exists(fileName))
	{
		std::cout << "The file: '" << fileName << "' was not found, please dump the game with Suwup's fork of il2cpp dumper and place '" << fileName << "' in the games root directory!\n";
		return;
	}

	std::ifstream stream(fileName);
	nlohmann::json script = nlohmann::json::parse(stream);

	auto cheat = new Idxhook::Cheat();

	auto& functionMap = Idxhook::Cheat::FunctionMap();

	auto functions = script["Methods"];
	for (auto& it : functions)
	{
		const uintptr_t offset = it["Address"].get<uintptr_t>();
		const std::string name = it["Name"].get<std::string>();

		functionMap.emplace(name, offset);
	}

	auto& typeInfoMap = Idxhook::Cheat::TypeInfoMap();

	auto typeInfos = script["TypeInfos"];
	for (auto& it : typeInfos)
	{
		const uintptr_t offset = it["Address"].get<uintptr_t>();
		const std::string signature = it["Signature"].get<std::string>();

		typeInfoMap.emplace(signature, offset);
	}
	
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
