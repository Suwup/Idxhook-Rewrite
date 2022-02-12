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

		static Il2CppClass* GetClass(const char* assm, const char* nms, const char* clazz) { return Get().IGetClass(assm, nms, clazz); }
		static Il2CppClass* GetClass(const Il2CppType* type) { return Get().IGetClass(type); }
		static Il2CppMethodPointer GetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc) { return Get().IGetMethod(assm, nms, clazz, funcName, argc); }
		static Il2CppMethodPointer GetMethod(Il2CppClass* clazz, const char* funcName, int argc) { return Get().IGetMethod(clazz, funcName, argc); }
		static Il2CppObject* GetType(const char* assm, const char* nms, const char* clazz) { return Get().IGetType(assm, nms, clazz); }

		static inline Il2cpp& Get() { return *s_Instance; }
	private:
		Il2CppClass* IGetClass(const char* assm, const char* nms, const char* clazz);
		Il2CppClass* IGetClass(const Il2CppType* type);
		Il2CppMethodPointer IGetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc);
		Il2CppMethodPointer IGetMethod(Il2CppClass* clazz, const char* funcName, int argc);
		Il2CppObject* IGetType(const char* assm, const char* nms, const char* clazz);
	public:
		USE_METHOD(DEF_METHOD);
	private:
		HMODULE m_Data = nullptr;
		Il2CppDomain* m_Domain = nullptr;
	private:
		static Il2cpp* s_Instance;
	};

}
