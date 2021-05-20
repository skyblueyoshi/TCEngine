

#include "TCMath.h"

namespace Tce {

    template<typename T>
    inline T TCMath::Clamp(T value, T min, T max) {
        if (value > max) return max;
        if (value < min) return min;
        return value;
    }

    template<typename T>
    inline T TCMath::Max(T a, T b) {
        return (a > b ? a : b);
    }

    template<typename T>
    inline T TCMath::Min(T a, T b) {
        return (a < b ? a : b);
    }

    inline float TCMath::Pow(float a, float b) {
        return std::powf(a, b);
    }

    inline float TCMath::Pow(float a, int b) {
        return std::powf(a, (float)b);
    }

    inline double TCMath::Pow(double a, double b) {
        return std::pow(a, b);
    }

    inline double TCMath::Pow(double a, int b) {
        return std::pow(a, b);
    }

    inline double TCMath::Sqrt(double a) {
        return std::sqrt(a);
    }

    inline float TCMath::Sqrt(float a) {
        return std::sqrtf(a);
    }

    inline float TCMath::Floor(float a) {
        return std::floorf(a);
    }

    inline double TCMath::Floor(double a) {
        return std::floor(a);
    }

    inline float TCMath::Ceil(float a) {
        return std::ceilf(a);
    }

    inline double TCMath::Ceil(double a) {
        return std::ceil(a);
    }

    inline int TCMath::Pow(int a, int b) {
        int result = 1;
        while (b) {
            if (b % 2)
            result *= a;
            b /= 2;
            a *= a;
        }
        return result;
    }

    template<typename T>
    inline int TCMath::CompareBySortKey(const void *pFirst, const void *pSecond) {
        auto &firstKey = reinterpret_cast<const T *>(pFirst)->__sortKey;
        auto &secondKey = reinterpret_cast<const T *>(pSecond)->__sortKey;
        if (firstKey == secondKey) return 0;
        if (firstKey > secondKey) return 1;
        return -1;
    }

    template<typename T>
    inline int TCMath::CompareBySelf(const void *pFirst, const void *pSecond) {
        return *reinterpret_cast<const T *>(pFirst) -
               *reinterpret_cast<const T *>(pSecond);
    }

    template<typename T>
    void TCMath::SortByKey(std::vector<T> &array) {
        qsort(array.data(), sizeof(T), array.size(), CompareBySortKey<T>);
    }

    inline int TCMath::PositiveMod(int a, int b) {
        int c = a % b;
        if (c < 0) c += b;
        return c;
    }
}