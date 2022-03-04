// k13
// Kyle J Burgess

#include "bytes.h"

#include <iostream>
#include <cstdint>
#include <cstring>

template<class T>
bool test_byteswap()
{
    // test single

    T a = 0, b = 0;

    for (size_t i = 0; i != sizeof(T); ++i)
    {
        reinterpret_cast<uint8_t*>(&a)[i] = i;
        reinterpret_cast<uint8_t*>(&b)[sizeof(T) - i - 1] = i;
    }

    bool r0 = (k13::byteswap(a) == b);
    bool r1 = (k13::byteswap(b) == a);

    if (!r0 || !r1)
    {
        std::cout << k13::byteswap(a) << ", " << b << " fail_0\n";
        return false;
    }

    // test array (in-place)

    T aArr[4] = { a, b, a, b };
    T bArr[4] = { b, a, b, a };

    k13::byteswap(aArr, 4);

    if (memcmp(aArr, bArr, 4 * sizeof(T)) != 0)
    {
        std::cout << "fail_1\n";
        return false;
    }

    // test array

    k13::byteswap(aArr, bArr, 4);
    k13::byteswap(bArr, 4);

    if (memcmp(aArr, bArr, 4 * sizeof(T)) != 0)
    {
        std::cout << "fail_2\n";
        return false;
    }

    return true;
}

int main()
{
    // reverse tests

    if (!test_byteswap<uint8_t>())
    {
        std::cout << "failed test_byteswap<uint8_t>()\n";
        return -1;
    }

    if (!test_byteswap<uint16_t>())
    {
        std::cout << "failed test_byteswap<uint16_t>()\n";
        return -1;
    }

    if (!test_byteswap<uint32_t>())
    {
        std::cout << "failed test_byteswap<uint32_t>()\n";
        return -1;
    }

    if (!test_byteswap<uint64_t>())
    {
        std::cout << "failed test_byteswap<uint64_t>()\n";
        return -1;
    }

    if (!test_byteswap<int8_t>())
    {
        std::cout << "failed test_byteswap<int8_t>()\n";
        return -1;
    }

    if (!test_byteswap<int16_t>())
    {
        std::cout << "failed test_byteswap<int16_t>()\n";
        return -1;
    }

    if (!test_byteswap<int32_t>())
    {
        std::cout << "failed test_byteswap<int32_t>()\n";
        return -1;
    }

    if (!test_byteswap<int64_t>())
    {
        std::cout << "failed test_byteswap<int64_t>()\n";
        return -1;
    }

    if (!test_byteswap<float>())
    {
        std::cout << "failed test_byteswap<float>()\n";
        return -1;
    }

    if (!test_byteswap<double>())
    {
        std::cout << "failed test_byteswap<double>()\n";
        return -1;
    }

    return 0;
}
