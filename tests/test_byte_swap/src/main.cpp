// k13
// Kyle J Burgess

#include "bytes.h"

#include <iostream>
#include <cstdint>
#include <cstring>

template<class T>
bool test_reverse()
{
    // test single

    T a = 0, b = 0;

    for (size_t i = 0; i != sizeof(T); ++i)
    {
        constexpr size_t shift = sizeof(T) * 8 - 8;

        a = (a << 8) | i;
        b = (b >> 8) | (i << shift);
    }

    bool r0 = (k13::byte_swap(a) == b);
    bool r1 = (k13::byte_swap(b) == a);

    if (!r0 || !r1)
    {
        return false;
    }

    // test array (in-place)

    T aArr[4] = { a, b, a, b };
    T bArr[4] = { b, a, b, a };

    k13::byte_swap(aArr, 4);

    if (memcmp(aArr, bArr, 4 * sizeof(T)) != 0)
    {
        return false;
    }

    // test array

    k13::byte_swap(aArr, bArr, 4);
    k13::byte_swap(bArr, 4);

    if (memcmp(aArr, bArr, 4 * sizeof(T)) != 0)
    {
        return false;
    }

    return true;
}

int main()
{
    // reverse tests

    if (!test_reverse<uint8_t>())
    {
        std::cout << "failed test_reverse<uint8_t>()\n";
        return -1;
    }

    if (!test_reverse<uint16_t>())
    {
        std::cout << "failed test_reverse<uint16_t>()\n";
        return -1;
    }

    if (!test_reverse<uint32_t>())
    {
        std::cout << "failed test_reverse<uint32_t>()\n";
        return -1;
    }

    if (!test_reverse<uint64_t>())
    {
        std::cout << "failed test_reverse<uint64_t>()\n";
        return -1;
    }

    return 0;
}
