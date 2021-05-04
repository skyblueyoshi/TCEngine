
#include "Rect.h"
#include <algorithm>

namespace Tce {

    template<typename T>
    Rect<T>::Rect(T _x, T _y, uint_t _width, uint_t _height)
            : x(_x), y(_y), width(_width), height(_height) {}

    template<typename T>
    bool Rect<T>::operator==(const Rect &other) const {
        return x == other.x &&
               y == other.y &&
               width == other.width &&
               height == other.height;
    }

    template<typename T>
    bool Rect<T>::operator!=(const Rect &other) const {
        return x != other.x ||
               y != other.y ||
               width != other.width ||
               height != other.height;
    }

    template<typename T>
    bool Rect<T>::Empty() const {
        return x == 0 && y == 0 &&
               width == 0 && height == 0;
    }

    template<typename T>
    bool Rect<T>::IsOverlapping(const Rect &other) const {
        return ((y + height > other.y) && (other.y + other.height > y))
               ? ((x + width > other.x) && (other.x + other.width > x))
               : false;
    }

    template<typename T>
    bool Rect<T>::IsPointIn(int pointX, int pointY) const {
        return ((T) pointX >= x) && ((T) pointX < x + width) &&
               ((T) pointY >= y) && ((T) pointY < y + height);
    }

    template<typename T>
    bool Rect<T>::IsPointIn(double pointX, double pointY) const {
        return ((T) pointX >= x) && ((T) pointX < x + width) &&
               ((T) pointY >= y) && ((T) pointY < y + height);
    }

    template<typename T>
    bool Rect<T>::IsPointIn(float pointX, float pointY) const {
        return ((T) pointX >= x) && ((T) pointX < x + width) &&
               ((T) pointY >= y) && ((T) pointY < y + height);
    }

    template<typename T>
    bool Rect<T>::IsPointIn(const Vector2 &vector2) const {
        return IsPointIn(vector2.x, vector2.y);
    }

    template<typename T>
    Rect <T> Rect<T>::Union(const Rect &other) {
        int minX = std::min(x, other.x);
        int minY = std::min(y, other.y);
        return {minX, minY,
                (uint_t) (std::max(GetRight(), other.GetRight()) - minX),
                (uint_t) (std::max(GetBottom(), other.GetBottom()) - minY)};
    }

    template<typename T>
    Rect <T> Rect<T>::Intersect(const Rect &other) {
        if (IsOverlapping(other)) {
            T left = std::max(x, other.x);
            T top = std::max(y, other.y);
            return {left, top,
                    (uint_t) (std::min(GetRight(), other.GetRight()) - left),
                    (uint_t) (std::min(GetBottom(), other.GetBottom()) - top)};
        }
        return {(T) 0, (T) 0, 0, 0};
    }

    template<typename T>
    T Rect<T>::GetRight() const {
        return x + width;
    }

    template<typename T>
    T Rect<T>::GetBottom() const {
        return y + height;
    }
}