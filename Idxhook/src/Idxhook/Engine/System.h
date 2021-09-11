#pragma once
#include <string>
#include <codecvt>
#include "Utils.h"

namespace Idxhook::System {

    template <typename T>
    class Array
	{
    public:
        union
		{
            Member(uint64_t, MaxLength, 0x18);
            Member(T*, Values[32], 0x20);
        };
    };

    template <typename T>
    class List
	{
    public:
        union
		{
            Member(Array<T>*, Items, 0x10);
            Member(int32_t, Size, 0x18);
        };
    };

    class String
	{
    public:
        union
		{
            Member(uint16_t, Chars[32], 0x14);
        };
    };

    namespace Utils {

        auto GetStringNative = [](System::String* str) -> std::string
		{
            std::u16string u16(reinterpret_cast<const char16_t*>(str->Chars));
            return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
        };

    }

}
