#pragma once

// Revo
#include <Revo/Config.hpp>

namespace rv
{
    /// Utility struct that combines all call operators of Ts... into one struct
    template <typename... Ts>
    struct Overloaded : Ts... { using Ts::operator()...; };

    /// Deduction guide for Overloaded struct to simplicity usage
    template <typename... Ts>
    Overloaded(Ts...) -> Overloaded<Ts...>;
}
