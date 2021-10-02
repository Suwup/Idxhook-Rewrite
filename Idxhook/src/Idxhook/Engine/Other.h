#pragma once
#include "System.h"

namespace Idxhook::PhotonNetwork {

	static void SetNickname(System::String* Nickname) { CALL_METHOD(void, (System::String*), (Nickname), ("PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "set_NickName", 1)); }
	static bool IsMasterClient() { CALL_METHOD(bool, (), (), ("PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsMasterClient", 0)); }

}

namespace Idxhook::Marshal {

	static System::String* PtrToStringAnsi(void* Pointer) { CALL_METHOD(System::String*, (void*), (Pointer), ("mscorlib", "System.Runtime.InteropServices", "Marshal", "PtrToStringAnsi", 1)); }

}
