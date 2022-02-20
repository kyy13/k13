// Kyle J Burgess

#ifndef K13_INT_FROM_BYTES_H
#define K13_INT_FROM_BYTES_H

#include <cassert>
#include <cstdint>

template<size_t NumBytes>
struct uint_from_bytes
{
    static_assert(
        NumBytes == 1 ||
        NumBytes == 2 ||
        NumBytes == 4 ||
        NumBytes == 8,
        "num bytes needs to be 1, 2 ,4, or 8");
};

template<>
struct uint_from_bytes<1u>
{
    using type = uint8_t;
};

template<>
struct uint_from_bytes<2u>
{
    using type = uint16_t;
};

template<>
struct uint_from_bytes<4u>
{
    using type = uint32_t;
};

template<>
struct uint_from_bytes<8u>
{
    using type = uint64_t;
};

template<size_t NumBytes>
struct int_from_bytes
{
    static_assert(
        NumBytes == 1 ||
        NumBytes == 2 ||
        NumBytes == 4 ||
        NumBytes == 8,
        "num bytes needs to be 1, 2 ,4, or 8");
};

template<>
struct int_from_bytes<1u>
{
    using type = int8_t;
};

template<>
struct int_from_bytes<2u>
{
    using type = int16_t;
};

template<>
struct int_from_bytes<4u>
{
    using type = int32_t;
};

template<>
struct int_from_bytes<8u>
{
    using type = int64_t;
};

#endif
