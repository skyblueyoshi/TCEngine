#pragma once

#include <vector>

namespace Tce {

    class MathHelper {
    public:
        // 将数值限定在给定区间[min, max]
        // @param value 被限定的数值
        // @param min 区间下限
        // @param max 区间上限
        // @return 限定后的值
        template<typename T>
        static inline T Clamp(T value, T min, T max) {
            if (value > max) return max;
            if (value < min) return min;
            return value;
        }

        // 获取较大值
        // @param a 比较值
        // @param b 比较值
        // @return 较大值
        template<typename T>
        static inline T Max(T a, T b) {
            return (a > b ? a : b);
        }

        // 获取较小值
        // @param a 比较值
        // @param b 比较值
        // @return 较小值
        template<typename T>
        static inline T Min(T a, T b) {
            return (a < b ? a : b);
        }

        template<typename T>
        static int CompareBySortKey(const void *pFirst, const void *pSecond) {
            return reinterpret_cast<T *>(pFirst)->__sortKey -
                   reinterpret_cast<T *>(pSecond)->__sortKey;
        }

        template<typename T>
        static int CompareBySelf(const void *pFirst, const void *pSecond) {
            return *reinterpret_cast<T *>(pFirst) -
                   *reinterpret_cast<T *>(pSecond);
        }

        typedef int(*COMPARATOR_FUNCTION)(const void *, const void *);

        // 排序
        // 使用每个类型的__sortKey来排序
        template<typename T>
        static void SortByKey(std::vector<T> &array) {
            qsort(array.data(), sizeof(T), array.size(), CompareBySortKey<T>);
        }
    };

}