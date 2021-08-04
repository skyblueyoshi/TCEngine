#pragma once

#include "Vector.h"

namespace Tce {

    struct Color {
        union {
            uint32_t _value{};
            struct {
                uint8_t blue;
                uint8_t green;
                uint8_t red;
                uint8_t alpha;
            };
        };

        Color() = default;

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

        // 构造函数
        // @param color 颜色
        // @param alpha alpha通道[0, 255]
        Color(const Color &color, int _alpha);

        // 构造函数
        // @param color 颜色
        // @param alpha alpha通道[0.0f, 1.0f]
        Color(const Color &color, float _alpha);

        // 构造函数
        // @param vector3 三维向量XYZ(RGB)
        Color(Vector3 vector3);

        // 构造函数
        // @param vector4 四维向量XYZW(RGBA)
        Color(Vector4 vector4);

        // 返回三维向量XYZ(RGB)
        Vector3 ToVector3();

        // 返回四维向量XYZW(RGBA)
        Vector4 ToVector4();

        bool operator==(const Color &color) const;

        bool operator!=(const Color &color) const;
    };
}

#include "Color.inl"