#ifndef PANS_INCLUDE_PANS_MACROS_H
#define PANS_INCLUDE_PANS_MACROS_H

#include <cassert>
#include <iostream>
#include <cstdint>

#define PANS_ASSERT(x) \
    if(!(x)) [[unlikely]]\
    {\
        std::cerr << __FILE__ << ":" << __LINE__ << "ASSERT FAILED: " << #x << "\nStacktrace: to do \n"; \
        assert(x);\
    }

#define PANS_ASSERT2(x, w)\
    if(!(x)) [[unlikely]]\
    {\
        std::cerr << __FILE__ << ":" << __LINE__ << "Assert" << #x << " faild. [" << w << "].\nStacktrace: to do \n"; \
        assert(x);\
    }

#define PANS_RETVAL(x, val)\
    do{\
        if(x) [[likely]] break;\
        PANS_ASSERT(x);\
        return val;\
    }while(0)

#define PANS_RETVAL(x, val, info)\
    do{\
        if(x) [[likely]] break;\
        PANS_ASSERT2(x, info);\
        return val;\
    }while(0)

#define INVALID64 (~0ULL)
#define INVALID32 0xFFFFFFFF
#define INVALID16 0xFFFF
#define INVALID8  0xFF

#define MAX_U8 0xFF
#define MAX_U16 0xFFFFF
#define MAX_U32 0xFFFFFFFF
#define MAX_U64 (~0ULL)

using u8 = uint8_t;
using s8 = int8_t;
using u16 = uint16_t;
using s16 = int16_t;
using u32 = uint32_t;
using s32 = int32_t;
using u64 = uint64_t;
using s64 = int64_t;

#endif