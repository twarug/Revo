#pragma once

// Compiler detection
#if defined(__clang__)
#   define RV_CXX_CLANG
#   define RV_CXX_NAME "LLVM/Clang " __VERSION__
#elif defined(__GNUG__)
#   define RV_CXX_GCC
#   define RV_CXX_NAME "GNU Compiler Collection " __VERSION__
#elif defined(_MSC_VER)
#   define RV_CXX_MSVC
#   define RV_CXX_NAME "Microsoft Visual C++ " _MSC_VER
#else
#   error Unknown compiler in use for Revo
#endif

// Stringification
#define RV_STR(__name) #__name
#define RV_XSTR(__name) RV_STR(__name)

// Concatenation
#define RV_CONCAT(__arg1, __arg2) __arg1##__arg2
#define RV_XCONCAT(__arg1, __arg2) RV_CONCAT(__arg1, __arg2)

// Asserting
#if defined(RV_DEBUG)
#   include <cassert>
#   define RV_ASSERT(__msg, __expr) assert(!(__msg) && (__expr))
#else
#   define RV_ASSERT(__msg, __expr)
#endif

// Source file informations
#define RV_FILE __FILE__
#define RV_LINE __LINE__
#define RV_HERE RV_FILE ":" RV_XSTR(RV_LINE)

// Function signature
#if defined(RV_CXX_CLANG) || defined(RV_CXX_GCC)
#   define RV_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(RV_CXX_MSVC)
#   define RV_FUNC_SIG __FUNCSIG__
#endif

// Soft magic types
namespace rv
{
    using size_t    = decltype(sizeof(char*));
    using ptrdiff_t = decltype((char*)0 - (char*)0);
    using nullptr_t = decltype(nullptr);
}

// Integer aliases
#include <cstdint>

// Logger utilities
#if defined(RV_DEBUG)

namespace rv
{
    inline class Logger* loggerGPtr = nullptr;
}

#define RV_LOG_INFO(...) rv::loggerGPtr->Log(rv::LogType::Info, __VA_ARGS__)
#define RV_LOG_WARNING(...) rv::loggerGPtr->Log(rv::LogType::Warning, __VA_ARGS__)
#define RV_LOG_ERROR(...) rv::loggerGPtr->Log(rv::LogType::Error, __VA_ARGS__)

#else

#define RV_LOG_INFO(...)
#define RV_LOG_WARNING(...)
#define RV_LOG_ERROR(...)

#endif
