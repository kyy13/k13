#include "pod_vector.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdint>

int main()
{
    size_t size = 10000000;
    clock_t t;

    // std
    {
        std::vector<uint32_t> arr0;
        std::vector<uint32_t> arr1;

        // Test 0
        t = clock();
        for (uint32_t i = 0; i <= size; i += 3)
        {
            uint32_t a[3] =
                {
                    i, i + 1, i + 2,
                };

            arr0.push_back(a[0]);
            arr0.push_back(a[1]);
            arr0.push_back(a[2]);
        }
        t = clock() - t;

        std::cout << "std, 3 pushes with arr = " << t << " ticks\n";

        // Test 1
        t = clock();
        for (uint32_t i = 0; i <= size; ++i)
        {
            arr1.push_back(i);
        }
        t = clock() - t;

        std::cout << "std, 3 pushes w/o arr = " << t << " ticks\n";
    }

    // k13
    {
        k13::pod_vector<uint32_t> arr0;
        k13::pod_vector<uint32_t> arr1;
        k13::pod_vector<uint32_t> arr2;

        // Test 0
        t = clock();
        for (uint32_t i = 0; i <= size; i += 3)
        {
            uint32_t a[3] =
                {
                    i, i + 1, i + 2,
                };

            arr0.push_back(a[0]);
            arr0.push_back(a[1]);
            arr0.push_back(a[2]);
        }
        t = clock() - t;

        std::cout << "k13, 3 pushes with arr = " << t << " ticks\n";

        // Test 1
        t = clock();
        for (uint32_t i = 0; i <= size; ++i)
        {
            arr1.push_back(i);
        }
        t = clock() - t;

        std::cout << "k13, 3 pushes w/o arr = " << t << " ticks\n";

        // Test 2
        t = clock();
        for (uint32_t i = 0; i <= size; i += 3)
        {
            uint32_t a[3] =
                {
                    i, i + 1, i + 2,
                };

            arr2.push_back(a, 3);
        }
        t = clock() - t;

        std::cout << "k13, 1 push with arr = " << t << " ticks\n";
    }

    return 0;
}
