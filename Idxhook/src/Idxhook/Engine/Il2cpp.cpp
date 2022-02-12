#include "ihpch.h"
#include "Il2cpp.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

namespace Idxhook {

#define SET_METHOD(ret, name, args) name = reinterpret_cast<decltype(name)>(GetProcAddress(m_Data, #name));

	Il2cpp* Il2cpp::s_Instance = nullptr;

	Il2cpp::Il2cpp()
	{
		s_Instance = this;

		m_Data = GetModuleHandleA("GameAssembly.dll");
		std::cout << "GameAssembly.dll: 0x" << std::hex << m_Data << "\n";
		if (!m_Data) return;

		USE_METHOD(SET_METHOD);

		m_Domain = il2cpp_domain_get();
		std::cout << "domain: 0x" << std::hex << m_Domain << "\n";
		if (!m_Domain) return;

		// Attach thread to prevent crashes
		il2cpp_thread_attach(m_Domain);
	}

	Il2cpp::~Il2cpp()
	{
		m_Data = nullptr;
		delete s_Instance;
	}

	Il2CppClass* Il2cpp::IGetClass(const char* assm, const char* nms, const char* clazz)
	{
		std::cout << "Getting class: " << clazz << " assembly: " << assm << " namespace: " << nms << "\n";

		auto assembly = il2cpp_domain_assembly_open(m_Domain, assm);
		std::cout << "assembly: 0x" << std::hex << assembly << "\n";
		if (!assembly) return nullptr;

		return il2cpp_class_from_name(assembly->image, nms, clazz);
	}

	Il2CppClass* Il2cpp::IGetClass(const Il2CppType* type)
	{
		return il2cpp_class_from_il2cpp_type(type);
	}

	Il2CppMethodPointer Il2cpp::IGetMethod(const char* assm, const char* nms, const char* clazz, const char* funcName, int argc)
	{
		std::cout << "Getting method: " << funcName << "\n";

		auto klazz = IGetClass(assm, nms, clazz);
		std::cout << "klazz: 0x" << std::hex << klazz << "\n";
		if (!klazz) return nullptr;

		return il2cpp_class_get_method_from_name(klazz, funcName, argc)->methodPointer;
	}

	Il2CppMethodPointer Il2cpp::IGetMethod(Il2CppClass* clazz, const char* funcName, int argc)
	{
		std::cout << "Getting method: " << funcName << "\n";

		return il2cpp_class_get_method_from_name(clazz, funcName, argc)->methodPointer;
	}

	Il2CppObject* Il2cpp::IGetType(const char* assm, const char* nms, const char* clazz)
	{
		std::cout << "Getting type from class: " << nms << "::" << clazz << "\n";

		auto klazz = IGetClass(assm, nms, clazz);
		std::cout << "klazz: 0x" << std::hex << klazz << "\n";
		if (!klazz) return nullptr;

		auto type = il2cpp_class_get_type(klazz);
		std::cout << "type: 0x" << std::hex << type << "\n";
		if (!type) return nullptr;

		return il2cpp_type_get_object(type);
	}

}
