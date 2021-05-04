#pragma once

#include <cstdint>

namespace Tce {

    class Memory {
    public:

        static const int32_t kNaN = (-1);

        template<typename T>
        static void _FillMemory(T *arr, size_t size, int fill);

        // 清空一个变量，仅清空内存数据
        // memset(p, 0, sizeof(T));
        template<typename T>
        static void ZeroVar(T &var);

        // 清空一个变量数组，仅清空内存数据
        // memset(p, 0, sizeof(T) * n);
        template<typename T, size_t n>
        static void ZeroArray(T(&arr)[n]);

        // 用NaN填充一个变量数组，仅填充内存数据
        // memset(p, 0, sizeof(T) * n);
        template<typename T, size_t n>
        static void NanArray(T(&arr)[n]);


        //清空一个动态分配的数组
        // memset(p, 0, sizeof(T) * size);
        template<typename T>
        static void ZeroDyArray(T *arr, size_t allocateSize, size_t size);

        // 使一个动态数组用-1填充
        // memset(p, -1, sizeof(T) * size)
        template<typename T>
        static void NanDyArray(T *arr, size_t allocateSize, size_t size);

        //复制一个数组
        template<typename T>
        static void CopyArray(T *des, T *src, size_t count);

        // 释放指针内存
        template<typename T>
        static void SafeDelete(T &ptr);

        // 释放指针指向的数组内存
        template<typename T>
        static void SafeDeleteArray(T &ptr);

        //判断父类引用是否拥有子类引用
        template<typename T, typename TBase>
        static bool IsInstanceOf(const TBase &e);

        //判断父类引用是否拥有子类引用
        template<typename T, typename TBase>
        static bool IsInstanceOf(TBase &e);

        //获取一个父类引用的子类引用
        template<typename T, typename TBase>
        static const T &GetInstanceOf(const TBase &e);

        //获取一个父类引用的子类引用
        template<typename T, typename TBase>
        static T &GetInstanceOf(TBase &e);
    };

}

#include "Memory.inl"