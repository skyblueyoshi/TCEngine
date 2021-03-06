#pragma once

#include "Vector.h"

namespace Tce {

    //表示一个矩形区域
    template<typename T>
    struct Rect {
        T x{};
        T y{};
        uint32_t width{};
        uint32_t height{};

        Rect() = default;
        Rect(T _x, T _y, uint32_t _width, uint32_t _height);

        bool operator==(const Rect &other) const;

        bool operator!=(const Rect &other) const;

        // 当前矩形是否为空
        // @return 是否为空
        bool Empty() const;

        // 是否与另外一个矩形重叠
        // @param other 另一个矩形
        // @return 是否重叠
        bool IsOverlapping(const Rect &other) const;

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        bool IsPointIn(int pointX, int pointY) const;

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        bool IsPointIn(double pointX, double pointY) const;

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        bool IsPointIn(float pointX, float pointY) const;

        // 指定点是否在矩形内
        // @param vector2 点
        // @return 是否在矩形内
        bool IsPointIn(const Vector2 &vector2) const;

        // 判断当前矩形是否完全包含另一个矩形
        // @param other 另一个矩形
        // @return 是否完全包含
        bool Contains(const Rect &other) const;

        // 获取与另一个矩形的最小包围矩形
        // @param other 另一个矩形
        // @return 最小包围矩形
        Rect Union(const Rect &other) const;

        // 获取与另一个矩形的交集矩形
        // @param other 另一个矩形
        // @return 交集矩形
        Rect Intersect(const Rect &other) const;

        // 获取矩形右侧横坐标
        // return 右侧横坐标
        T GetRight() const;

        // 获取矩形底侧纵坐标
        // return 底侧纵坐标
        T GetBottom() const;

        // 获取矩形中心横坐标
        // return 中心横坐标
        T GetCenterX() const;

        // 获取矩形中心纵坐标
        // return 中心纵坐标
        T GetCenterY() const;
    };

    typedef Rect<int> RectInt;
    typedef Rect<float> RectFloat;
    typedef Rect<double> RectDouble;

}

#include "Rect.inl"