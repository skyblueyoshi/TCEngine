#pragma once

#include <cstdint>

namespace Tce {

    // ARGB颜色
    union Color {
        uint32_t _value{};
        struct ARGB {
            uint8_t alpha;
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            ARGB() = default;
            ARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
        } argb;

        // 构造函数
        // @param value 符合ARGB格式的32位无符号整数
        Color(uint32_t value);

        // 构造函数
        // @param r 红色通道[0, 255]
        // @param g 绿色通道[0, 255]
        // @param b 蓝色通道[0, 255]
        Color(int r, int g, int b);

        // 构造函数
        // @param r 红色通道[0.0f, 1.0f]
        // @param g 绿色通道[0.0f, 1.0f]
        // @param b 蓝色通道[0.0f, 1.0f]
        Color(float r, float g, float b);

        // 构造函数
        // @param a alpha通道[0, 255]
        // @param r 红色通道[0, 255]
        // @param g 绿色通道[0, 255]
        // @param b 蓝色通道[0, 255]
        Color(int a, int r, int g, int b);

        // 构造函数
        // @param a alpha通道[0.0f, 1.0f]
        // @param r 红色通道[0.0f, 1.0f]
        // @param g 绿色通道[0.0f, 1.0f]
        // @param b 蓝色通道[0.0f, 1.0f]
        Color(float a, float r, float g, float b);

        // 构造函数
        // @param a alpha通道[0, 255]
        // @param r 红色通道[0, 255]
        // @param g 绿色通道[0, 255]
        // @param b 蓝色通道[0, 255]
        Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

        bool operator==(const Color& color) const {
            return _value == color._value;
        }

        bool operator!=(const Color& color) const {
            return _value != color._value;
        }
    };

}