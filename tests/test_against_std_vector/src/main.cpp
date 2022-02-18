// PODserializer
// Kyle J Burgess

#include "pod_vector.h"

#include <cstdint>

template<class T>
bool check_equality(const k13::pod_vector<T>& pv, const std::vector<T>& v)
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

template<class T>
bool test()
{
    k13::pod_vector<T> pv;
    std::vector<T> v;

    if(pv.size() != v.size())
    {
        return false;
    }

    pv = k13::pod_vector<T>(128);
    v = std::vector<T>(128);

    if(pv.size() != v.size())
    {
        return false;
    }

    pv = k13::pod_vector<T>(128, -1);
    v = std::vector<T>(128, -1);

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
    if (!test<uint8_t>())
    {
        return -1;
    }

    if (!test<uint16_t>())
    {
        return -1;
    }

    if (!test<uint32_t>())
    {
        return -1;
    }

    if (!test<uint64_t>())
    {
        return -1;
    }

    if (!test<int8_t>())
    {
        return -1;
    }

    if (!test<int16_t>())
    {
        return -1;
    }

    if (!test<int32_t>())
    {
        return -1;
    }

    if (!test<int64_t>())
    {
        return -1;
    }

    if (!test<float>())
    {
        return -1;
    }

    if (!test<double>())
    {
        return -1;
    }

    return 0;
}
