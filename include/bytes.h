// k13
// Kyle J Burgess

#ifndef K13_BYTES_H
#define K13_BYTES_H

#include <cstdint>
#include <cstring>

template<class T>
void reverse_byte_order(T* x)
{
    if constexpr (sizeof(T) != 1)
    {
        uint8_t tmp;
        auto a = reinterpret_cast<uint8_t*>(x);

        if constexpr (sizeof(T) == 2)
        {
            tmp = a[0];
            a[0] = a[1];
            a[1] = tmp;
        }
        else if constexpr (sizeof(T) == 4)
        {
            tmp = a[0];
            a[0] = a[3];
            a[3] = tmp;
            tmp = a[1];
            a[1] = a[2];
            a[2] = tmp;
        }
        else if constexpr (sizeof(T) == 8)
        {
            tmp = a[0];
            a[0] = a[7];
            a[7] = tmp;
            tmp = a[1];
            a[1] = a[6];
            a[6] = tmp;
            tmp = a[2];
            a[2] = a[5];
            a[5] = tmp;
            tmp = a[3];
            a[3] = a[4];
            a[4] = tmp;
        }
    }
}

template<class T>
void reverse_byte_order(T* dst, const T* src)
{
    if constexpr (sizeof(T) == 1)
    {
        *dst = *src;
    }
    else
    {
        auto a = reinterpret_cast<uint8_t*>(dst);
        auto b = reinterpret_cast<const uint8_t*>(src);

        if constexpr (sizeof(T) == 2)
        {
            a[0] = b[1];
            a[1] = b[0];
        }
        else if constexpr (sizeof(T) == 4)
        {
            a[0] = b[3];
            a[1] = b[2];
            a[2] = b[1];
            a[3] = b[0];
        }
        else if constexpr (sizeof(T) == 8)
        {
            a[0] = b[7];
            a[1] = b[6];
            a[2] = b[5];
            a[3] = b[4];
            a[4] = b[3];
            a[5] = b[2];
            a[6] = b[1];
            a[7] = b[0];
        }
    }
}

template<class T>
void reverse_byte_order(T* x, size_t n)
{
    if constexpr (sizeof(T) != 1)
    {
        T* end = x + n;

        for (; x != end; ++x)
        {
            reverse_byte_order(x);
        }
    }
}

template<class T>
void reverse_byte_order(T* dst, const T* src, size_t n)
{
    if constexpr (sizeof(T) == 1)
    {
        memcpy(dst, src, n);
    }
    else
    {
        T* end = dst + n;

        for (; dst != end; ++dst)
        {
            reverse_byte_order(dst, src);
            ++src;
        }
    }
}

#endif
