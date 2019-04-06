#pragma once

// C++
#include <utility>

namespace rv
{
    namespace detail
    {
        /// Default IsReferenceWrapper trait that yields false
        template <typename T>
        struct IsReferenceWrapper : std::false_type {};

        /// Specialization of IsReferenceWrapper trait that yields true
        template <typename T>
        struct IsReferenceWrapper<std::reference_wrapper<T>> : std::true_type {};

        /// Variable alias for IsReferenceWrapper trait
        template <typename T>
        inline constexpr auto IsReferenceWrapper_v = IsReferenceWrapper<T>::value;

        /// rv::Invoke overload for methods and class fields
        template <typename Class, typename R, typename T, typename... Args>
        constexpr decltype(auto) InvokeImpl(R Class::* member, T&& obj, Args&&... args)
        {
            if constexpr (std::is_member_function_pointer_v<decltype(member)>)
            {
                if constexpr (std::is_base_of_v<Class, std::decay_t<T>>)
                {
                    return (std::forward<T>(obj).*member)(std::forward<Args>(args)...);
                }
                else if constexpr (IsReferenceWrapper_v<std::decay_t<T>>)
                {
                    return (obj.get().*member)(std::forward<Args>(args)...);
                }
                else
                {
                    return ((*std::forward<T>(obj)).*member)(std::forward<Args>(args)...);
                }
            }
            else
            {
                static_assert(std::is_member_object_pointer_v<decltype(member)>);
                static_assert(sizeof...(args) == 0u);

                if constexpr (std::is_base_of_v<Class, std::decay_t<T>>)
                {
                    return std::forward<T>(obj).*member;
                }
                else if constexpr (IsReferenceWrapper_v<std::decay_t<T>>)
                {
                    return obj.get().*member;
                }
                else
                {
                    return (*std::forward<T>(obj)).*member;
                }
            }
        }

        /// rv::Invoke overload for free functions
        template <typename F, typename... Args>
        constexpr decltype(auto) InvokeImpl(F&& f, Args&&... args)
        {
            return std::forward<F>(f)(std::forward<Args>(args)...);
        }
    }

    /// Invokes f with given args...
    template <typename F, typename... Args>
    constexpr decltype(auto) Invoke(F&& f, Args&&... args) noexcept(std::is_nothrow_invocable_v<F, Args...>)
    {
        return detail::InvokeImpl(std::forward<F>(f), std::forward<Args>(args)...);
    }
}

#define RV_LIFT(__f)\
    [](auto&&... args) noexcept(noexcept(__f(std::forward<decltype(args)>(args)...)))\
        -> decltype(__f(std::forward<decltype(args)>(args)...))\
    { return __f(std::forward<decltype(args)>(args)...); }
