#pragma once

#include <cstdint>
#include "Vector.h"

namespace Tce {

    //表示一个矩形区域
    template<typename T>
    struct Rect {
        T x{};
        T y{};
        uint_t width{};
        uint_t height{};

        Rect(T _x, T _y, uint_t _width, uint_t _height);

        bool operator==(const Rect &other) const;

        bool operator!=(const Rect &other) const;

        // 当前矩形是否为空
        // @return 是否为空
        bool Empty() const;

        // 是否与另外一个矩形重叠
        // @param other 另一个矩形
        // @return 是否重叠
        inline bool IsOverlapping(const Rect &other) const;

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        inline bool IsPointIn(int pointX, int pointY) const;

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        inline bool IsPointIn(double pointX, double pointY) const;

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        inline bool IsPointIn(float pointX, float pointY) const;

        // 指定点是否在矩形内
        // @param vector2 点
        // @return 是否在矩形内
        inline bool IsPointIn(const Vector2 &vector2) const;

        // 获取与另一个矩形的最小包围矩形
        // @param other 另一个矩形
        // @return 最小包围矩形
        inline Rect Union(const Rect &other);

        // 获取与另一个矩形的交集矩形
        // @param other 另一个矩形
        // @return 交集矩形
        inline Rect Intersect(const Rect &other);

        // 获取矩形右侧横坐标
        // return 右侧横坐标
        inline T GetRight() const;

        // 获取矩形底侧纵坐标
        // return 底侧纵坐标
        inline T GetBottom() const;
    };

    typedef Rect<int> RectInt;
    typedef Rect<float> RectFloat;
    typedef Rect<double> RectDouble;

}

#include "Rect.inl"