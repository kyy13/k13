#include "pod_vector.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdint>

int main()
{
    size_t size = 100000000;

    clock_t t;

    struct uint3
    {
        uint32_t a;
        uint32_t b;
        uint32_t c;
    };

    // std
    {
        std::vector<uint32_t> arr0;
        std::vector<uint32_t> arr1;
        std::vector<uint3> arr2;

        //arr0.reserve(size + 3);
        //arr1.reserve(size + 3);
        //arr2.reserve(size/3 + 3);

        // Test 0
        t = clock();
        for (uint32_t i = 0; i < size; i += 9)
        {
            uint32_t a[9] =
                {
                    i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7, i + 8,
                };

            arr0.push_back(a[0]);
            arr0.push_back(a[1]);
            arr0.push_back(a[2]);
            arr0.push_back(a[3]);
            arr0.push_back(a[4]);
            arr0.push_back(a[5]);
            arr0.push_back(a[6]);
            arr0.push_back(a[7]);
            arr0.push_back(a[8]);
        }
        t = clock() - t;

        std::cout << "std, 3 pushes with arr = " << t << " ticks\n";

        // Test 1
        t = clock();
        for (uint32_t i = 0; i < size; ++i)
        {
            arr1.push_back(i);
        }
        t = clock() - t;

        std::cout << "std, 3 pushes w/o arr = " << t << " ticks\n";

        // Test 2
        t = clock();
        for (uint32_t i = 0; i < size; i += 3)
        {
            uint3 a =
                {
                    .a = i,
                    .b = i + 1,
                    .c = i + 2,
                };

            arr2.push_back(a);
        }
        t = clock() - t;

        std::cout << "std, 1 push with arr3 = " << t << " ticks\n";
    }

    // k13
    {
        k13::pod_vector<uint32_t> arr0;
        k13::pod_vector<uint32_t> arr1;
        k13::pod_vector<uint32_t> arr2;
        k13::pod_vector<uint3> arr3;

        //arr0.reserve(size + 3);
        //arr1.reserve(size + 3);
        //arr2.reserve(size + 3);
        //arr3.reserve(size/3 + 3);

        // Test 0
        t = clock();
        for (uint32_t i = 0; i < size; i += 9)
        {
            uint32_t a[9] =
                {
                    i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7, i + 8,
                };

            arr0.push_back(a[0]);
            arr0.push_back(a[1]);
            arr0.push_back(a[2]);
            arr0.push_back(a[3]);
            arr0.push_back(a[4]);
            arr0.push_back(a[5]);
            arr0.push_back(a[6]);
            arr0.push_back(a[7]);
            arr0.push_back(a[8]);
        }
        t = clock() - t;

        std::cout << "k13, 3 pushes with arr = " << t << " ticks\n";

        // Test 1
        t = clock();
        for (uint32_t i = 0; i < size; ++i)
        {
            arr1.push_back(i);
        }
        t = clock() - t;

        std::cout << "k13, 3 pushes w/o arr = " << t << " ticks\n";

        // Test 2
        t = clock();
        for (uint32_t i = 0; i < size; i += 9)
        {
            uint32_t a[9] =
                {
                    i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7, i + 8,
                };

            arr2.push_back(a, 9);
        }
        t = clock() - t;

        std::cout << "k13, 1 push with arr = " << t << " ticks\n";

        // Test 3
        t = clock();
        for (uint32_t i = 0; i < size; i += 3)
        {
            uint3 a =
                {
                    .a = i,
                    .b = i + 1,
                    .c = i + 2,
                };

            arr3.push_back(a);
        }
        t = clock() - t;

        std::cout << "k13, 1 push with arr3 = " << t << " ticks\n";
    }

    return 0;
}
