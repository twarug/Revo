#pragma once

// Revo
#include <Revo/Utility/Functional.hpp>

namespace  rv
{
    ///
    template <auto... vMembers>
    struct MembersExtractor
    {
        template <typename T, typename F>
        static void ForEach(T&& object, F function)
        {
            (Invoke(function, std::forward<T>(object), vMembers), ...);
        }
    };

    ///
    template <typename>
    struct MembersOf : MembersExtractor<> {};
}
