#pragma once

#include <vector>

namespace Tce {

    class TCMath {
    public:
        // 将数值限定在给定区间[min, max]
        // @param value 被限定的数值
        // @param min 区间下限
        // @param max 区间上限
        // @return 限定后的值
        template<typename T>
        static T Clamp(T value, T min, T max);

        // 获取较大值
        // @param a 比较值
        // @param b 比较值
        // @return 较大值
        template<typename T>
        static T Max(T a, T b);

        // 获取较小值
        // @param a 比较值
        // @param b 比较值
        // @return 较小值
        template<typename T>
        static T Min(T a, T b);

        //求余获取正数（a % b 得到非负数）
        inline int PositiveMod(int a, int b);

        template<typename T>
        static int CompareBySortKey(const void *pFirst, const void *pSecond);

        template<typename T>
        static int CompareBySelf(const void *pFirst, const void *pSecond);

        typedef int(*COMPARATOR_FUNCTION)(const void *, const void *);

        // 排序
        // 使用每个类型的__sortKey来排序
        template<typename T>
        static void SortByKey(std::vector<T> &array);
    };

}

#include "TCMath.inl"