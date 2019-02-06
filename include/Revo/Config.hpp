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