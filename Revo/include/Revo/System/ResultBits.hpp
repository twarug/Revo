#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <cstdint>

namespace rv
{
    ///
    enum class ResultBits : int32_t
    {
        
    };

    ///
    constexpr ResultBits operator & (ResultBits lhs, ResultBits rhs)
    {
        return ResultBits{ static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs) };
    }

    ///
    constexpr ResultBits operator | (ResultBits lhs, ResultBits rhs)
    {
        return ResultBits{ static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs) };
    }

    ///
    constexpr ResultBits operator ^ (ResultBits lhs, ResultBits rhs)
    {
        return ResultBits{ static_cast<int32_t>(lhs) ^ static_cast<int32_t>(rhs) };
    }
}
