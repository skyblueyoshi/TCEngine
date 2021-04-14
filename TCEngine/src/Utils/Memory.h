#pragma once

#include <memory>
#include <cstring>

namespace Tce {
    // 清空一个变量，仅清空内存数据
    // memset(p, 0, sizeof(T));
    template<typename T>
    inline void ZeroVar(T &arr) {
        memset(&arr, 0, sizeof(T));
    }

    // 清空一个变量数组，仅清空内存数据
    // memset(p, 0, sizeof(T) * n);
    template<typename T, size_t n>
    inline void ZeroArray(T(&arr)[n]) {
        memset(arr, 0, sizeof(T) * n);
    }

    // 释放指针内存
    template<typename T>
    inline void SafeDelete(T &ptr) {
        if (ptr) {
            delete ptr;
            ptr = NULL;
        }
    }

    // 释放指针指向的数组内存
    template<typename T>
    inline void SafeDeleteArray(T &ptr) {
        if (ptr) {
            delete[] ptr;
            ptr = NULL;
        }
    }

}
