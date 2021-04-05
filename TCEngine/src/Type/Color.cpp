#include "Color.h"
#include "MathHelper.h"

namespace Tce {

    Color::Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
        : argb(a, r, g, b) {}

    Color::Color(uint32_t value) : _value(value) {}

    Color::Color(int a, int r, int g, int b) {
        if (((a | r | g | b) & 0xFFFFFF00) != 0) {
            auto _a = (uint8_t) MathHelper::Clamp(a, 0, 255);
            auto _r = (uint8_t) MathHelper::Clamp(r, 0, 255);
            auto _g = (uint8_t) MathHelper::Clamp(g, 0, 255);
            auto _b = (uint8_t) MathHelper::Clamp(b, 0, 255);
            argb.alpha = _a;
            argb.red = _r;
            argb.green = _g;
            argb.blue = _b;
        } else {
            argb.alpha = (uint8_t) a;
            argb.red = (uint8_t) r;
            argb.green = (uint8_t) g;
            argb.blue = (uint8_t) b;
        }
    }

    Color::Color(int r, int g, int b)
            : Color(255, r, g, b) {}

    Color::Color(float r, float g, float b)
            : Color((int) (r * 255), (int) (g * 255), (int) (b * 255)) {}

    Color::Color(float a, float r, float g, float b)
            : Color((int) (a * 255), (int) (r * 255), (int) (g * 255), (int) (b * 255)) {}

    Color::ARGB::ARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
            : alpha(a), red(r), green(g), blue(b) {}
}