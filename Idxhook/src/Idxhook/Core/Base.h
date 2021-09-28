#pragma once

namespace Idxhook::Offsets {

	#define OFFSET_METHOD(namespaze, name, ...) namespace Methods::namespaze { inline uintptr_t name = 0; }
	#define OFFSET_TYPE_INFO(name) namespace TypeInfo { inline uintptr_t name = 0; }
	#define OFFSET_HOOK(namespaze, name, ...) namespace Hooks::namespaze { inline void* name = nullptr; }
	
	#include "Idxhook/Engine/Offsets.h"
	
	#undef OFFSET_METHOD
	#undef OFFSET_TYPE_INFO
	#undef OFFSET_HOOK

}
