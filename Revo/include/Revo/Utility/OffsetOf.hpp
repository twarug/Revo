#pragma once

// Revo
#include <Revo/Core.hpp>

namespace rv
{
    /// Returns pointer offset of structure member
    template <typename T, typename Class>
    void const* OffsetPtrOf(T Class::* member)
    {
        return &(reinterpret_cast<Class*>(0)->*member);
    }

    /// Returns offset of structure member in bytes
    template <typename T, typename Class>
    size_t OffsetOf(T Class::* member)
    {
        return reinterpret_cast<size_t>(OffsetPtrOf(member));
    }
}
