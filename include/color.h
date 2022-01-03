// Kyle J Burgess

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H

#include <cstdint>
#include <cmath>

// Resulting color from color_a over color_b
// format is 0xAARRGGBB
[[nodiscard]]
uint32_t color_over_op(uint32_t a, uint32_t b);

// Lerp colors
[[nodiscard]]
uint32_t color_lerp(uint32_t a, uint32_t b, float lerpFactor);

// component-wise RGB to SRGB
constexpr float r_to_sr(float a)
{
    if (a <= 0.00031308f)
    {
        return 12.92f * a;
    }

    return 1.055f * powf(a, 0.4166666667f) - 0.055f;
}

// component-wise SRGB to RGB
constexpr float sr_to_r(float s)
{
    if (s <= 0.04045)
    {
        return s / 12.92f;
    }

    return powf((s + 0.055f) / 1.055f, 2.4);
}

// linear RGB to SRGB, 0xAARRGGBB
constexpr uint32_t rgb_to_srgb(uint32_t c)
{
    constexpr float oneOver255 = 1.0f / 255.0f;

    float r = r_to_sr(oneOver255 * static_cast<float>((c >> 16) & 0xffu));
    float g = r_to_sr(oneOver255 * static_cast<float>((c >>  8) & 0xffu));
    float b = r_to_sr(oneOver255 * static_cast<float>((c >>  0) & 0xffu));

    uint32_t c_ =
        (c & 0xff000000u) |
        (static_cast<uint32_t>(r * 255.0f) << 16) |
        (static_cast<uint32_t>(g * 255.0f) <<  8) |
        (static_cast<uint32_t>(b * 255.0f) <<  0);

    return c_;
}

// SRGB to linear RGB, 0xAARRGGBB
constexpr uint32_t srgb_to_rgb(uint32_t c)
{
    constexpr float oneOver255 = 1.0f / 255.0f;

    float r = sr_to_r(oneOver255 * static_cast<float>((c >> 16) & 0xffu));
    float g = sr_to_r(oneOver255 * static_cast<float>((c >>  8) & 0xffu));
    float b = sr_to_r(oneOver255 * static_cast<float>((c >>  0) & 0xffu));

    uint32_t c_ =
        (c & 0xff000000u) |
        (static_cast<uint32_t>(r * 255.0f) << 16) |
        (static_cast<uint32_t>(g * 255.0f) <<  8) |
        (static_cast<uint32_t>(b * 255.0f) <<  0);

    return c_;
}

#endif
