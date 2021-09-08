#pragma once
#include <windows.h>
#include <cstdint>

#define CreateName(Prefix, Name) Prefix##Name
#define CreatePadName(Number) CreateName(Pad, Number)
#define Pad(Size) std::byte CreatePadName(__COUNTER__)[Size]
#define Member(Type, Name, Offset) struct { Pad(Offset); Type Name; }

#define GetGameAssembly() GetModuleHandleA("GameAssembly")

namespace Idxhook {

	namespace Utils {

		static constexpr auto ReleaseFailure = [](const char* message) -> void
		{
			MessageBoxA(nullptr, message, "Sussy baka", MB_OK | MB_ICONERROR);
		};

		static constexpr auto IsValid = [](void* pointer) -> bool
		{
			return pointer > (void*)0x10000;
		};

		template <typename T>
		static constexpr auto GetTypeFromTypeInfo = [](std::uintptr_t address) -> T*
		{
			return reinterpret_cast<T*>(**(std::uintptr_t**)(*(std::uintptr_t*)address + 0xb8));
		};

	}

	namespace Memory {

		static constexpr auto GetRVA = [](std::uintptr_t address) -> std::uintptr_t
		{
			return reinterpret_cast<std::uintptr_t>(GetGameAssembly()) + address;
		};

		template <class T>
		static constexpr auto GetRVAPointer = [](std::uintptr_t address) -> T*
		{
			auto ptr = reinterpret_cast<T*>(GetRVA(address));
			if (!ptr) Utils::ReleaseFailure("Invalid VA pointer (outdated?)");
			return ptr;
		};

		template <typename T, typename... Args>
		static constexpr auto CallFunction = [](std::uintptr_t address, Args... args) -> T
		{
			return reinterpret_cast<T(*)(Args...)>(address)(std::forward<Args>(args)...);
		};

	}

}
