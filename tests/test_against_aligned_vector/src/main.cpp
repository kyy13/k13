// k13
// Kyle J Burgess

#include "pod_vector.h"
#include "aligned_pod_vector.h"

#include <cstdint>

template<class T, size_t N>
bool check_equality(const k13::pod_vector<T>& pv, const k13::aligned_pod_vector<T, N>& v)
{
    if (pv.size() != v.size())
    {
        return false;
    }

    for (size_t i = 0; i != pv.size(); ++i)
    {
        if (pv[i] != v[i])
        {
            return false;
        }
    }

    return true;
}

template<class T, size_t N>
bool test()
{
    k13::pod_vector<T> pv;
    k13::aligned_pod_vector<T, N> v;

    if(pv.size() != v.size())
    {
        return false;
    }

    pv = k13::pod_vector<T>(128);
    v = k13::aligned_pod_vector<T, N>(128);

    if(pv.size() != v.size())
    {
        return false;
    }

    pv = k13::pod_vector<T>(128, -1);
    v = k13::aligned_pod_vector<T, N>(128, -1);

    if (!check_equality(pv, v))
    {
        return false;
    }

    pv.resize(64);
    v.resize(64);

    if (!check_equality(pv, v))
    {
        return false;
    }

    pv.resize(128, -2);
    v.resize(128, -2);

    if (!check_equality(pv, v))
    {
        return false;
    }

    pv.resize(100, -3);
    v.resize(100, -3);

    if (!check_equality(pv, v))
    {
        return false;
    }

    for (size_t i = 0; i != 100; ++i)
    {
        pv.push_back(i);
        v.push_back(i);

        if (!check_equality(pv, v))
        {
            return false;
        }
    }

    for (size_t i = 0; i != 50; ++i)
    {
        pv.pop_back();
        v.pop_back();

        if (!check_equality(pv, v))
        {
            return false;
        }
    }

    pv.clear();
    v.clear();

    if (!check_equality(pv, v))
    {
        return false;
    }

    pv.reserve(500);
    v.reserve(500);

    if (!check_equality(pv, v))
    {
        return false;
    }

    pv.shrink_to_fit();
    v.shrink_to_fit();

    if (pv.capacity() != v.capacity())
    {
        return false;
    }

    return true;
}

int main()
{
    // U8

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

    // U16

    if (!test<uint16_t, 4>())
    {
        return -1;
    }

    if (!test<uint16_t, 8>())
    {
        return -1;
    }

    // U32

    if (!test<uint32_t, 8>())
    {
        return -1;
    }

    // S8

    if (!test<int8_t, 2>())
    {
        return -1;
    }

    if (!test<int8_t, 4>())
    {
        return -1;
    }

    if (!test<int8_t, 8>())
    {
        return -1;
    }

    // S16

    if (!test<int16_t, 4>())
    {
        return -1;
    }

    if (!test<int16_t, 8>())
    {
        return -1;
    }

    // S32

    if (!test<int32_t, 8>())
    {
        return -1;
    }

    // F

    if (!test<float, 8>())
    {
        return -1;
    }

    return 0;
}
