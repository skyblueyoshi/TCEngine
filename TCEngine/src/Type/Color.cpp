#include "Color.h"
#include "MathHelper.h"

namespace Tce {

    Color::Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
            : alpha(a), red(r), green(g), blue(b) {}

    Color::Color(uint32_t value) : _value(value) {}

    Color::Color(int a, int r, int g, int b) {
        if (((a | r | g | b) & 0xFFFFFF00) != 0) {
            alpha = (uint8_t) MathHelper::Clamp(a, 0, 255);
            red = (uint8_t) MathHelper::Clamp(r, 0, 255);
            green = (uint8_t) MathHelper::Clamp(g, 0, 255);
            blue = (uint8_t) MathHelper::Clamp(b, 0, 255);
        } else {
            alpha = (uint8_t) a;
            red = (uint8_t) r;
            green = (uint8_t) g;
            blue = (uint8_t) b;
        }
    }

    Color::Color(int r, int g, int b)
            : Color(255, r, g, b) {}

    Color::Color(float r, float g, float b)
            : Color((int) (r * 255), (int) (g * 255), (int) (b * 255)) {}

    Color::Color(float a, float r, float g, float b)
            : Color((int) (a * 255), (int) (r * 255), (int) (g * 255), (int) (b * 255)) {}


    Color::Color(Vector4 vector4)
            : Color(vector4.w, vector4.x, vector4.y, vector4.z) {}

    Color::Color(Vector3 vector3)
            : Color(vector3.x, vector3.y, vector3.z) {}

    Vector4 Color::ToVector4() {
        return {(float)red / 255.0f, (float)green / 255.0f, (float)blue / 255.0f,
                       (float)alpha / 255.0f};
    }

    Vector3 Color::ToVector3() {
        return {(float)red / 255.0f, (float)green / 255.0f, (float)blue / 255.0f};
    }

    Color::Color(const Color &color, int _alpha) {
        _value = color._value;
        if ((_alpha & 0xFFFFFF00) != 0) {
            alpha = (uint8_t) MathHelper::Clamp(_alpha, 0, 255);
        } else {
            alpha = (uint8_t) _alpha;
        }
    }

    Color::Color(const Color &color, float _alpha)
            : Color(color, (int) (_alpha * 255)) {}

}