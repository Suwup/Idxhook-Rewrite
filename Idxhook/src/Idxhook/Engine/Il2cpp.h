#pragma once

#include <Idxhook/Engine/Il2cppMethods.h>
#include <minwindef.h>

namespace Idxhook {

#define DEF_METHOD(ret, name, args) ret(*name)args = nullptr;

	class Il2cpp
	{
	public:
		Il2cpp();
		~Il2cpp();

		static Il2CppClass* GetClass(const char* assm, const char* nms, const char* clazz);
		static Il2CppMethodPointer GetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc);

		static inline Il2cpp& Get() { return *s_Instance; }
	private:
		Il2CppClass* IGetClass(const char* assm, const char* nms, const char* clazz);
		Il2CppMethodPointer IGetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc);
	private:
		USE_METHOD(DEF_METHOD);
	private:
		HMODULE m_Data = nullptr;
	private:
		static Il2cpp* s_Instance;
	};

}
