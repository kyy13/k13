// k13
// Kyle J Burgess

#include "aligned_pod_vector.h"

#include <cstdint>

template<class T, size_t N>
bool test()
{
    k13::aligned_pod_vector<T, N> pv(128);

    for (size_t i = 0; i != 128; i += N)
    {
        auto address = reinterpret_cast<size_t>(&pv[i]);

        if ((address % N) != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    if (!test<uint8_t, 2>())
    {
        return -1;
    }

    if (!test<uint8_t, 4>())
    {
        return -1;
    }

    if (!test<uint8_t, 8>())
    {
        return -1;
    }

    if (!test<int16_t, 4>())
    {
        return -1;
    }

    if (!test<int16_t, 8>())
    {
        return -1;
    }

    if (!test<float, 8>())
    {
        return -1;
    }

    return 0;
}
