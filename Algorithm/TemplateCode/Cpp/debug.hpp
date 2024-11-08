#pragma once
#ifndef __CP_DEBUG_LIB_POWER_BY_FMT__
#define __CP_DEBUG_LIB_POWER_BY_FMT__

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif

#include <format>
#include <print>
#include <string>

// #include "fmt/printf.h"
// #include "fmt/std.h"
// #include "fmt/core.h"
// #include "fmt/format.h"
// #include "fmt/ranges.h"

namespace DebugLib {
inline struct ErrorPrint {
    template <typename _Tp> void Print(const char *name, const _Tp &value);

    template <typename _Tp> std::string FormatAble(const _Tp &value);
} debugErr;
} // namespace DebugLib

template <typename _Tp>
void DebugLib::ErrorPrint::Print(const char *name, const _Tp &value) {
    std::print(stderr, "{0}={1}, ", name, FormatAble(value));
}
template <typename _Tp>
std::string DebugLib::ErrorPrint::FormatAble(const _Tp &value) {
    return std::format("{0}", value);
}

#define __CP_DEBUG_GET_MACRO_ARGS(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME

#define __CP_DEBUG_CERR_PRINT1(V1) DebugLib::debugErr.Print(#V1, V1);
// #define __CP_DEBUG_CERR_PRINT1(V1) fmt::print(stderr, "{0}={1} ", #V1, V1);

#define __CP_DEBUG_CERR_PRINT2(V1, V2)                                         \
    __CP_DEBUG_CERR_PRINT1(V1) __CP_DEBUG_CERR_PRINT1(V2)
#define __CP_DEBUG_CERR_PRINT3(V1, V2, V3)                                     \
    __CP_DEBUG_CERR_PRINT2(V1, V2) __CP_DEBUG_CERR_PRINT1(V3)
#define __CP_DEBUG_CERR_PRINT4(V1, V2, V3, V4)                                 \
    __CP_DEBUG_CERR_PRINT3(V1, V2, V3) __CP_DEBUG_CERR_PRINT1(V4)
#define __CP_DEBUG_CERR_PRINT5(V1, V2, V3, V4, V5)                             \
    __CP_DEBUG_CERR_PRINT4(V1, V2, V3, V4) __CP_DEBUG_CERR_PRINT1(V5)
#define __CP_DEBUG_CERR_PRINT6(V1, V2, V3, V4, V5, V6)                         \
    __CP_DEBUG_CERR_PRINT5(V1, V2, V3, V4, V5) __CP_DEBUG_CERR_PRINT1(V6)
#define __CP_DEBUG_CERR_PRINT7(V1, V2, V3, V4, V5, V6, V7)                     \
    __CP_DEBUG_CERR_PRINT6(V1, V2, V3, V4, V5, V6) __CP_DEBUG_CERR_PRINT1(V7)

#define __CP_DEBUG_ERROR_PRINT(...)                                            \
    do {                                                                       \
        __CP_DEBUG_GET_MACRO_ARGS(                                             \
            __VA_ARGS__, __CP_DEBUG_CERR_PRINT7, __CP_DEBUG_CERR_PRINT6,       \
            __CP_DEBUG_CERR_PRINT5, __CP_DEBUG_CERR_PRINT4,                    \
            __CP_DEBUG_CERR_PRINT3, __CP_DEBUG_CERR_PRINT2,                    \
            __CP_DEBUG_CERR_PRINT1, ...)(__VA_ARGS__)                          \
            std::print(stderr, "\n");                                          \
    } while (false)

#define debug(...)                                                             \
    std::print(stderr, "[{0}]: ", __LINE__);                                   \
    __CP_DEBUG_ERROR_PRINT(__VA_ARGS__)

#endif