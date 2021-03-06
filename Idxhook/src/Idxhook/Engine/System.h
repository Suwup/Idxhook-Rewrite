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

}
