

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

    template<typename T>
    inline int TCMath::CompareBySortKey(const void *pFirst, const void *pSecond) {
        return reinterpret_cast<const T *>(pFirst)->__sortKey -
               reinterpret_cast<const T *>(pSecond)->__sortKey;
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