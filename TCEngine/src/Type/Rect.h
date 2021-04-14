#pragma once

#include <sys/types.h>
#include <algorithm>
#include "Vector.h"

namespace Tce {

    //表示一个矩形区域
    template<typename T>
    struct Rect {
        T x{};
        T y{};
        uint_t width{};
        uint_t height{};

        Rect(T _x, T _y, uint_t _width, uint_t _height)
                : x(_x), y(_y), width(_width), height(_height) {}

        bool operator==(const Rect &other) const {
            return x == other.x &&
                   y == other.y &&
                   width == other.width &&
                   height == other.height;
        }

        bool operator!=(const Rect &other) const {
            return x != other.x ||
                   y != other.y ||
                   width != other.width ||
                   height != other.height;
        }

        // 当前矩形是否为空
        // @return 是否为空
        bool Empty() const {
            return x == 0 && y == 0 &&
                   width == 0 && height == 0;
        }

        // 是否与另外一个矩形重叠
        // @param other 另一个矩形
        // @return 是否重叠
        inline bool IsOverlapping(const Rect &other) const {
            return ((y + height > other.y) && (other.y + other.height > y))
                   ? ((x + width > other.x) && (other.x + other.width > x))
                   : false;
        }

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        inline bool IsPointIn(int pointX, int pointY) const {
            return ((T) pointX >= x) && ((T) pointX < x + width) &&
                   ((T) pointY >= y) && ((T) pointY < y + height);
        }

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        inline bool IsPointIn(double pointX, double pointY) const {
            return ((T) pointX >= x) && ((T) pointX < x + width) &&
                   ((T) pointY >= y) && ((T) pointY < y + height);
        }

        // 指定点是否在矩形内
        // @param pointX 点横坐标
        // @param pointY 点纵坐标
        // @return 是否在矩形内
        inline bool IsPointIn(float pointX, float pointY) const {
            return ((T) pointX >= x) && ((T) pointX < x + width) &&
                   ((T) pointY >= y) && ((T) pointY < y + height);
        }

        // 指定点是否在矩形内
        // @param vector2 点
        // @return 是否在矩形内
        inline bool IsPointIn(const Vector2 &vector2) const {
            return IsPointIn(vector2.x, vector2.y);
        }

        // 获取与另一个矩形的最小包围矩形
        // @param other 另一个矩形
        // @return 最小包围矩形
        inline Rect Union(const Rect &other) {
            int minX = std::min(x, other.x);
            int minY = std::min(y, other.y);
            return Rect(minX, minY,
                        (uint_t) (std::max(GetRight(), other.GetRight()) - minX),
                        (uint_t) (std::max(GetBottom(), other.GetBottom()) - minY));
        }

        // 获取与另一个矩形的交集矩形
        // @param other 另一个矩形
        // @return 交集矩形
        inline Rect Intersect(const Rect &other) {
            if (IsOverlapping(other)) {
                T left = std::max(x, other.x);
                T top = std::max(y, other.y);
                return Rect(left, top,
                            (uint_t) (std::min(GetRight(), other.GetRight()) - left),
                            (uint_t) (std::min(GetBottom(), other.GetBottom()) - top));
            }
            return Rect((T) 0, (T) 0, 0, 0);
        }

        // 获取矩形右侧横坐标
        // return 右侧横坐标
        inline T GetRight() const {
            return x + width;
        }

        // 获取矩形底侧纵坐标
        // return 底侧纵坐标
        inline T GetBottom() const {
            return y + height;
        }
    };

    typedef Rect<int> RectInt;
    typedef Rect<float> RectFloat;
    typedef Rect<double> RectDouble;

}