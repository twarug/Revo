#pragma once

// Revo
#include <Revo/Core.hpp>

namespace rv
{
    /// Returns amount of the Unicode bytes in given range
    template <typename InputIt>
    size_t GetUnicodeBytesCount(InputIt begin, InputIt end)
    {
        size_t n = 0;

        while (begin != end)
        {
            if (*begin >= 0)
            {
                ++begin;
            }
            else
            {
                if ((*begin & 0xF0) == 0xF0)
                {
                    begin += 4;
                }
                else if ((*begin & 0xE0) == 0xE0)
                {
                    begin += 3;
                }
                else
                {
                    begin += 2;
                }
            }

            ++n;
        }

        return n;
    }

    /// Returns amount of the UTF8 characters in given range
    template <typename InputIt>
    size_t GetUTF8BytesCount(InputIt begin, InputIt end)
    {
        size_t n = 0;

        while (begin != end)
        {
            if ((~*begin & 0xFFFFFF80) == 0xFFFFFF80)
            {
                n += 1u;
            }
            else if ((~*begin & 0xFFFFF800) == 0xFFFFF800)
            {
                n += 2u;
            }
            else if ((~*begin & 0xFFFF0000) == 0xFFFF0000)
            {
                n += 3u;
            }
            else
            {
                n += 4u;
            }

            ++begin;
        }

        return n;
    }

    /// Converts given UTF8 range to Unicode one
    template <typename InputIt, typename OutputIt>
    void UTF8ToUnicode(InputIt begin, InputIt end, OutputIt dst)
    {
        uint32_t helper;
        uint32_t aux;

        while (begin != end)
        {
            if (*begin >= 0)
            {
                *dst = *begin;

                ++begin;
            }
            else
            {
                helper = 0;

                if ((*begin & 0xF0) == 0xF0)
                {
                    aux = *begin; aux &= 0x07; aux <<= 18; helper |= aux; ++begin;
                    aux = *begin; aux &= 0x3F; aux <<= 12; helper |= aux; ++begin;
                    aux = *begin; aux &= 0x3F; aux <<=  6; helper |= aux; ++begin;
                    aux = *begin; aux &= 0x3F;             helper |= aux; ++begin;

                    *dst = helper;
                }
                else if ((*begin & 0xE0) == 0xE0)
                {
                    aux = *begin; aux &= 0x0F; aux <<= 12; helper |= aux; ++begin;
                    aux = *begin; aux &= 0x3F; aux <<=  6; helper |= aux; ++begin;
                    aux = *begin; aux &= 0x3F;             helper |= aux; ++begin;

                    *dst = helper;
                }
                else
                {
                    aux = *begin; aux &= 0x1F; aux <<=  6; helper |= aux; ++begin;
                    aux = *begin; aux &= 0x3F;             helper |= aux; ++begin;

                    *dst = helper;
                }
            }

            ++dst;
        }
    }

    /// Converts given Unicode range to UTF8 one
    template <typename InputIt, typename OutputIt>
    void UnicodeToUTF8(InputIt begin, InputIt end, OutputIt dst)
    {
        uint32_t aux;

        while (begin != end)
        {
            aux = *begin;

            if ((~aux & 0xFFFFFF80) == 0xFFFFFF80)
            {
                *dst = aux;
            }
            else if ((~aux & 0xFFFFF800) == 0xFFFFF800)
            {
                *dst = ((aux & 0xFC0)   >>  6) | 0xC0; ++dst;
                *dst =  (aux & 0x3F)           | 0x80;
            }
            else if ((~aux & 0xFFFF0000) == 0xFFFF0000)
            {
                *dst = ((aux & 0x3F000) >> 12) | 0xE0; ++dst;
                *dst = ((aux & 0xFC0)   >>  6) | 0x80; ++dst;
                *dst =  (aux & 0x3F)           | 0x80;
            }
            else
            {
                *dst = ((aux & 0xFC000) >> 18) | 0xF0; ++dst;
                *dst = ((aux & 0x3F000) >> 12) | 0x80; ++dst;
                *dst = ((aux & 0xFC0)   >>  6) | 0x80; ++dst;
                *dst =  (aux & 0x3F)           | 0x80;
            }

            ++begin;
            ++dst;
        }
    }
}
