// k13
// Kyle J Burgess

#include "scalar.h"

#include <iostream>
#include <cstdint>
#include <cstring>

int main()
{
    k13::scalar_t a = 5;
    k13::scalar_t b = 1;

    a += 5;
    ++a;

    if ((a - 10) != b)
    {
        return -1;
    }

    return 0;
}
