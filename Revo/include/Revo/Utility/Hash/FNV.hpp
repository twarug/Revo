#pragma once

// Revo
#include <Revo/Utility/Hash/HashTypes.hpp>

namespace rv
{
    namespace detail
    {
        ///
        template <typename T>
        inline constexpr T fnvOffset;

        ///
        template <>
        inline constexpr Hash32_t fnvOffset<Hash32_t> = 0x811C9DC5u;

        ///
        template <>
        inline constexpr Hash64_t fnvOffset<Hash64_t> = 0xCBF29CE484222325ull;

        ///
        template <>
        inline constexpr Hash128_t fnvOffset<Hash128_t> = (static_cast<Hash128_t>(0x6C62272E07BB0142ull) << 64) | static_cast<Hash128_t>(0x62B821756295C58Dull);

        ///
        template <typename T>
        inline constexpr T fnvPrime;

        ///
        template <>
        inline constexpr Hash32_t fnvPrime<Hash32_t> = 0x1000193u;

        ///
        template <>
        inline constexpr Hash64_t fnvPrime<Hash64_t> = 0x100000001B3ull;

        ///
        template <>
        inline constexpr Hash128_t fnvPrime<Hash128_t> = (static_cast<Hash128_t>(0x0000000001000000ull) << 64) | static_cast<Hash128_t>(0x000000000000013Bull);

        ///
        template <typename T, bool vIsAlternative, T vOffset = fnvOffset<T>, T vPrime = fnvPrime<T>>
        struct FNV
        {
            using Hash_t = T;

            static constexpr Hash_t offset = vOffset;
            static constexpr Hash_t prime  = vPrime;

            /// Computes Fowler–Noll–Vo hash from given null-terminated source
            template <typename InputIt>
            static constexpr Hash_t Compute(InputIt begin)
            {
                Hash_t value = offset;

                while (*begin)
                {
                    if constexpr (vIsAlternative)
                    {
                        value ^= *begin;
                        value *= prime;
                    }
                    else
                    {
                        value *= prime;
                        value ^= *begin;
                    }
                    
                    ++begin;
                }

                return value;
            }

            /// Computes Fowler–Noll–Vo hash from given range
            template <typename InputIt>
            static constexpr Hash_t Compute(InputIt begin, InputIt end)
            {
                Hash_t value = offset;

                while (begin != end)
                {
                    if constexpr (vIsAlternative)
                    {
                        value ^= *begin;
                        value *= prime;
                    }
                    else
                    {
                        value *= prime;
                        value ^= *begin;
                    }
                    
                    ++begin;
                }

                return value;
            }
        };
    }

    /// Hasher alias for 32-bit Fowler–Noll–Vo v0
    using FNV0_32 = detail::FNV<Hash32_t, false, 0>;

    /// Hasher alias for 64-bit Fowler–Noll–Vo v0
    using FNV0_64 = detail::FNV<Hash64_t, false, 0>;

    /// Hasher alias for 128-bit Fowler–Noll–Vo v0
    using FNV0_128 = detail::FNV<Hash128_t, false, 0>;

    /// Hasher alias for 32-bit Fowler–Noll–Vo v1
    using FNV1_32 = detail::FNV<Hash32_t, false>;

    /// Hasher alias for 64-bit Fowler–Noll–Vo v1
    using FNV1_64 = detail::FNV<Hash64_t, false>;

    /// Hasher alias for 128-bit Fowler–Noll–Vo v1
    using FNV1_128 = detail::FNV<Hash128_t, false>;

    /// Hasher alias for 32-bit alternative Fowler–Noll–Vo v1
    using FNV1a_32 = detail::FNV<Hash32_t, true>;

    /// Hasher alias for 64-bit alternative Fowler–Noll–Vo v1
    using FNV1a_64 = detail::FNV<Hash64_t, true>;

    /// Hasher alias for 128-bit alternative Fowler–Noll–Vo v1
    using FNV1a_128 = detail::FNV<Hash128_t, true>;
}
