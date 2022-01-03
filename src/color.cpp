// Kyle J Burgess

#include "Color.h"
#include <cassert>

uint32_t color_over_op(uint32_t a, uint32_t b)
{
    uint32_t t0, t1, t2;
    uint32_t c_02, c_13, c_ffh;

    t0 = a >> 24u;
    t1 = b >> 24u;

    if (t0 == 0xffu || t1 == 0x00u)
    {
        return a;
    }

    if (t0 == 0x00u)
    {
        return b;
    }

    if (t1 == 0xffu)
    {
        t1 = (a & 0xff00ff00u) >> 8u; // _13
        a &= 0x00ff00ffu; // _02

        t2 = (b & 0xff00ff00u) >> 8u; // _13
        b &= 0x00ff00ffu; // _02

        c_02 = (a * t0 + b * (0x100u - t0)) >> 8u;
        c_13 = t1 * t0 + t2 * (0x100u - t0);

        return 0xff000000u | (c_02 & 0x00ff00ffu) | (c_13 & 0x0000ff00u);
    }

    c_ffh = (0x10000u - (0x100u - t0) * (0x100u - t1)) >> 8u; // < 0x100
    t2 = (t0 << 8u) / c_ffh;

    t0 = (a & 0xff00ff00u) >> 8u; // _13
    a &= 0x00ff00ffu; // _02

    t1 = (b & 0xff00ff00u) >> 8u; // _13
    b &= 0x00ff00ffu; // _02

    c_02 = (a * t2 + b * (0x100u - t2)) >> 8u;
    c_13 = t0 * t2 + t1 * (0x100u - t2);

    return (c_ffh << 24u) | (c_02 & 0x00ff00ffu) | (c_13 & 0x0000ff00u);
}

uint32_t color_lerp(uint32_t a, uint32_t b, float lerpFactor)
{
    auto f = static_cast<uint32_t>(lerpFactor * 256.0f);
    assert(f <= 256u);

    uint32_t a_13 = (a & 0xff00ff00u) >> 8u; // _13
    a &= 0x00ff00ffu; // _02

    uint32_t b_13 = (b & 0xff00ff00u) >> 8u; // _13
    b &= 0x00ff00ffu; // _02

    uint32_t c_02 = (a * f + b * (0x100 - f)) >> 8u;
    uint32_t c_13 = a_13 * f + b_13 * (0x100 - f);

    return (c_02 & 0x00ff00ffu) | (c_13 & 0xff00ff00u);
}
