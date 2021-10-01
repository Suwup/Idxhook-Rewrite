#include "ihpch.h"
#include "Il2cpp.h"

namespace Idxhook {

#define SET_METHOD(ret, name, args) name = reinterpret_cast<decltype(name)>(GetProcAddress(m_Data, #name));

	Il2cpp* Il2cpp::s_Instance = nullptr;

	Il2cpp::Il2cpp()
	{
		s_Instance = this;

		m_Data = GetModuleHandleA("GameAssembly.dll");
		std::cout << "GameAssembly.dll: 0x" << std::hex << m_Data << std::endl;
		if (!m_Data) return;

		USE_METHOD(SET_METHOD);

		// Attach thread to prevent crashes
		il2cpp_thread_attach(il2cpp_domain_get());
	}

	Il2cpp::~Il2cpp()
	{
		m_Data = nullptr;
		delete s_Instance;
	}

	Il2CppClass* Il2cpp::GetClass(const char* assm, const char* nms, const char* clazz)
	{
		return Get().IGetClass(assm, nms, clazz);
	}

	Il2CppMethodPointer Il2cpp::GetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc)
	{
		return Get().IGetMethod(assm, nms, clazz, funcName, argc);
	}

	Il2CppClass* Il2cpp::IGetClass(const char* assm, const char* nms, const char* clazz)
	{
		auto domain = il2cpp_domain_get();
		std::cout << "domain: 0x" << std::hex << domain << std::endl;
		if (!domain) return nullptr;

		auto assembly = il2cpp_domain_assembly_open(domain, assm);
		std::cout << "assembly: 0x" << std::hex << assembly << std::endl;
		if (!assembly) return nullptr;

		return il2cpp_class_from_name(assembly->image, nms, clazz);
	}

	Il2CppMethodPointer Il2cpp::IGetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc)
	{
		auto klazz = IGetClass(assm, nms, clazz);
		std::cout << "klazz: 0x" << std::hex << klazz << std::endl;
		if (!klazz) return nullptr;

		return il2cpp_class_get_method_from_name(klazz, funcName, argc)->methodPointer;
	}

}
