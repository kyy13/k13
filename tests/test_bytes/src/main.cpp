// k13
// Kyle J Burgess

#include "bytes.h"

#include <cstdint>

int main()
{
    // reverse uint32_t test (in-place)

    uint32_t x = 0x01020304u;

    reverse_byte_order(&x);

    if (x != 0x04030201u)
    {
        return -1;
    }

    // reverse uint32_t test

    uint32_t y;

    reverse_byte_order(&y, &x);

    if (y != 0x01020304u)
    {
        return -1;
    }

    // reverse uint32_t array test (in-place)

    uint32_t u[3] =
        {
            0x01020304u,
            0x05060708u,
            0x090A0B0Cu,
        };

    uint32_t v[3] =
        {
            0x04030201u,
            0x08070605u,
            0x0C0B0A09u,
        };

    reverse_byte_order(u, 3);

    if (memcmp(u, v, sizeof(u)) != 0)
    {
        return -1;
    }

    uint32_t t[3];

    // reverse uint32_t array test

    reverse_byte_order(u, 3);
    reverse_byte_order(t, u, 3);

    if (memcmp(t, v, sizeof(v)) != 0)
    {
        return -1;
    }

    // single byte (uint8_t) cases

    uint8_t a = 0x04u;

    reverse_byte_order(&a);

    if (a != 0x04u)
    {
        return -1;
    }

    uint8_t b = 0x04u;

    reverse_byte_order(&b, &a);

    if (b != 0x04u)
    {
        return -1;
    }

    uint8_t c[3] =
        {
            0x01u,
            0x02u,
            0x03u,
        };

    uint8_t d[3] =
        {
            0x01u,
            0x02u,
            0x03u,
        };

    reverse_byte_order(c, 3);

    if (memcmp(c, d, sizeof(c)) != 0)
    {
        return -1;
    }

    reverse_byte_order(c, d, 3);

    if (memcmp(c, d, sizeof(c)) != 0)
    {
        return -1;
    }

    return 0;
}
