#pragma once
#include "Il2cppMethods.h"

#include <windows.h>
#include <iostream>

namespace Idxhook {

#define SET_METHOD(ret, name, ...) name = reinterpret_cast<decltype(name)>(GetProcAddress(m_Assembly, #name));
#define DEF_METHOD(ret, name, ...) using def_##name = ret(*)__VA_ARGS__; \
	def_##name name = nullptr;

	class Il2cpp
	{
	public:
		Il2cpp()
		{
			s_Instance = this;

			m_Assembly = GetModuleHandleA("GameAssembly.dll");
			std::cout << "GameAssembly.dll: 0x" << std::hex << m_Assembly << std::endl;
			if (!m_Assembly) return;

			USE_METHOD(SET_METHOD);

			// Attach thread to prevent crashes
			il2cpp_thread_attach(il2cpp_domain_get());
		}

		static Il2CppMethodPointer GetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc)
		{
			return Get().IGetMethod(assm, nms, clazz, funcName, argc);
		}

		static Il2cpp& Get() { return *s_Instance; }
	private:
		Il2CppMethodPointer IGetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc)
		{
			auto domain = il2cpp_domain_get();
			std::cout << "domain: 0x" << std::hex << domain << std::endl;
			if (!domain) return nullptr;

			auto assembly = il2cpp_domain_assembly_open(domain, assm);
			std::cout << "assembly: 0x" << std::hex << assembly << std::endl;
			if (!assembly) return nullptr;

			auto klazz = il2cpp_class_from_name(assembly->image, nms, clazz);
			std::cout << "klazz: 0x" << std::hex << klazz << std::endl;
			if (!klazz) return nullptr;

			return il2cpp_class_get_method_from_name(klazz, funcName, argc)->methodPointer;
		}
	private:
		USE_METHOD(DEF_METHOD);
	private:
		HMODULE m_Assembly = nullptr;
	private:
		static Il2cpp* s_Instance;
	};

	Il2cpp* Il2cpp::s_Instance = nullptr;

}
