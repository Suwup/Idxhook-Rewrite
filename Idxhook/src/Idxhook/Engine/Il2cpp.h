#pragma once
#include <cstdint>

using Il2CppMethodPointer = void(*)();

struct MethodInfo;

struct VirtualInvokeData
{
	Il2CppMethodPointer methodPtr;
	const MethodInfo* method;
};

struct Il2CppType
{
	void* data;
	unsigned int bits;
};

struct Il2CppClass;

struct Il2CppObject
{
	Il2CppClass* klass;
	void* monitor;
};

union Il2CppRGCTXData
{
	void* rgctxDataDummy;
	const MethodInfo* method;
	const Il2CppType* type;
	Il2CppClass* klass;
};

struct Il2CppClass_1
{
	void* image;
	void* gc_desc;
	const char* name;
	const char* namespaze;
	Il2CppType* byval_arg;
	Il2CppType* this_arg;
	Il2CppClass* element_class;
	Il2CppClass* castClass;
	Il2CppClass* declaringType;
	Il2CppClass* parent;
	void* generic_class;
	void* typeDefinition;
	void* interopData;
	void* fields;
	void* events;
	void* properties;
	void* methods;
	Il2CppClass** nestedTypes;
	Il2CppClass** implementedInterfaces;
	void* interfaceOffsets;
};

struct Il2CppArrayBounds
{
	int32_t length;
	int32_t lower_bound;
};

struct MethodInfo
{
	Il2CppMethodPointer methodPointer;
	void* invoker_method;
	const char* name;
	Il2CppClass* declaring_type;
	const Il2CppType* return_type;
	const void* parameters;
	union
	{
		const Il2CppRGCTXData* rgctx_data;
		const void* methodDefinition;
	};
	union
	{
		const void* genericMethod;
		const void* genericContainer;
	};
	int32_t customAttributeIndex;
	uint32_t token;
	uint16_t flags;
	uint16_t iflags;
	uint16_t slot;
	uint8_t parameters_count;
	uint8_t bitflags;
};

struct Il2CppClass_2
{
	Il2CppClass** typeHierarchy;
	uint32_t cctor_started;
	uint32_t cctor_finished;
	uint64_t cctor_thread;
	int32_t genericContainerIndex;
	int32_t customAttributeIndex;
	uint32_t instance_size;
	uint32_t actualSize;
	uint32_t element_size;
	int32_t native_size;
	uint32_t static_fields_size;
	uint32_t thread_static_fields_size;
	int32_t thread_static_fields_offset;
	uint32_t flags;
	uint32_t token;
	uint16_t method_count;
	uint16_t property_count;
	uint16_t field_count;
	uint16_t event_count;
	uint16_t nested_type_count;
	uint16_t vtable_count;
	uint16_t interfaces_count;
	uint16_t interface_offsets_count;
	uint8_t typeHierarchyDepth;
	uint8_t genericRecursionDepth;
	uint8_t rank;
	uint8_t minimumAlignment;
	uint8_t packingSize;
	uint8_t bitflags1;
	uint8_t bitflags2;
};

struct Il2CppClass
{
	Il2CppClass_1 _1;
	void* static_fields;
	Il2CppRGCTXData* rgctx_data;
	Il2CppClass_2 _2;
	VirtualInvokeData vtable[255];
};
