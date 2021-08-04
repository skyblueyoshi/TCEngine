
#include "Rect.h"

namespace Tce {

    template<typename T>
    Rect<T>::Rect(T _x, T _y, uint32_t _width, uint32_t _height)
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
        return ((GetBottom() > other.y) && (other.GetBottom() > y))
               ? ((GetRight() > other.x) && (other.GetRight() > x))
               : false;
    }

    template<typename T>
    bool Rect<T>::IsPointIn(int pointX, int pointY) const {
        return ((T) pointX >= x) && ((T) pointX < GetRight()) &&
               ((T) pointY >= y) && ((T) pointY < GetBottom());
    }

    template<typename T>
    bool Rect<T>::IsPointIn(double pointX, double pointY) const {
        return ((T) pointX >= x) && ((T) pointX < GetRight()) &&
               ((T) pointY >= y) && ((T) pointY < GetBottom());
    }

    template<typename T>
    bool Rect<T>::IsPointIn(float pointX, float pointY) const {
        return ((T) pointX >= x) && ((T) pointX < GetRight()) &&
               ((T) pointY >= y) && ((T) pointY < GetBottom());
    }

    template<typename T>
    bool Rect<T>::IsPointIn(const Vector2 &vector2) const {
        return IsPointIn(vector2.x, vector2.y);
    }

    template<typename T>
    bool Rect<T>::Contains(const Rect &other) const {
        return other.x >= x && other.y >= y && 
            other.GetRight() <= GetRight() && other.GetBottom() <= GetBottom();
    }

    template<typename T>
    Rect <T> Rect<T>::Union(const Rect &other) const {
        int minX = TCMath::Min(x, other.x);
        int minY = TCMath::Min(y, other.y);
        return {minX, minY,
                (uint32_t) (TCMath::Max(GetRight(), other.GetRight()) - minX),
                (uint32_t) (TCMath::Max(GetBottom(), other.GetBottom()) - minY)};
    }

    template<typename T>
    Rect <T> Rect<T>::Intersect(const Rect &other) const {
        if (IsOverlapping(other)) {
            T left = TCMath::Max(x, other.x);
            T top = TCMath::Max(y, other.y);
            return {left, top,
                    (uint32_t) (TCMath::Min(GetRight(), other.GetRight()) - left),
                    (uint32_t) (TCMath::Min(GetBottom(), other.GetBottom()) - top)};
        }
        return {(T) 0, (T) 0, 0, 0};
    }

    template<typename T>
    T Rect<T>::GetRight() const {
        return (T)(x + width);
    }

    template<typename T>
    T Rect<T>::GetBottom() const {
        return (T)(y + height);
    }

    template<typename T>
    T Rect<T>::GetCenterX() const {
        return (T)(x + width / 2);
    }

    template<typename T>
    T Rect<T>::GetCenterY() const {
        return (T)(y + height / 2);
    }
}