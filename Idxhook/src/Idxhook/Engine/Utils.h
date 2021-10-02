#pragma once
#include <windows.h>
#include <cstdint>

#define CreateName(Prefix, Name) Prefix##Name
#define CreatePadName(Number) CreateName(Pad, Number)
#define Pad(Size) std::byte CreatePadName(__COUNTER__)[Size]
#define Member(Type, Name, Offset) struct { Pad(Offset); Type Name; }

namespace Idxhook::Utils {

	static constexpr auto IsValid = [](void* pointer) -> bool
	{
		return pointer > (void*)0x10000;
	};

}
