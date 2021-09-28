#pragma once
#include "System.h"

namespace Idxhook::PhotonNetwork {

	static void SetNickname(System::String* Nickname) { return Memory::CallFunction<void, System::String*>(Offsets::Methods::PhotonNetwork::set_NickName, Nickname); }
	static bool IsMasterClient() { return Memory::CallFunction<bool>(Offsets::Methods::PhotonNetwork::get_IsMasterClient); }

}

namespace Idxhook::Marshal {

	static System::String* PtrToStringAnsi(void* Pointer) { return Memory::CallFunction<System::String*, void*>(Offsets::Methods::Marshal::PtrToStringAnsi, Pointer); }

}
