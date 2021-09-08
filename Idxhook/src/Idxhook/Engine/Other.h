#pragma once
#include "System.h"
#include "Offsets.h"

namespace Idxhook::PhotonNetwork {

	static void SetNickname(System::String* Nickname) { return Memory::CallFunction<void, System::String*>(Offsets::Methods::PhotonNetwork::SetNickName, Nickname); }

}

namespace Idxhook::Marshal {

	static System::String* PtrToStringAnsi(void* Pointer) { return Memory::CallFunction<System::String*, void*>(Offsets::Methods::Marshal::PtrToStringAnsi, Pointer); }

}
