
#include "Memory.h"
#include <memory>
#include <cstring>

namespace Tce {

    template<typename T>
    inline void Memory::ZeroVar(T &var) {
        _FillMemory(&var, 1, 0);
    }

    template<typename T, size_t n>
    inline void Memory::ZeroArray(T(&arr)[n]) {
        ZeroDyArray(arr, n, n);
    }

    template<typename T, size_t n>
    inline void Memory::NanArray(T(&arr)[n]) {
        NanDyArray(arr, n, n);
    }

    template<typename T>
    inline void Memory::ZeroDyArray(T *arr, size_t allocateSize, size_t size) {
        assert(size <= allocateSize);
        _FillMemory(arr, size, 0);
    }

    template<typename T>
    inline void Memory::NanDyArray(T *arr, size_t allocateSize, size_t size) {
        assert(size <= allocateSize);
        _FillMemory(arr, size, kNaN);
    }

    template<typename T>
    inline void Memory::CopyArray(T *des, T *src, size_t count) {
        for (int i = 0; i < count; i++) {
            des[i] = src[i];
        }
    }

    template<typename T>
    inline void Memory::_FillMemory(T *arr, size_t size, int fill) {
        memset(arr, fill, sizeof(T) * size);
    }

    template<typename T>
    inline void Memory::SafeDelete(T &ptr) {
        if (ptr) {
            delete ptr;
            ptr = NULL;
        }
    }

    template<typename T>
    inline void Memory::SafeDeleteArray(T &ptr) {
        if (ptr) {
            delete[] ptr;
            ptr = NULL;
        }
    }

    template<typename T, typename TBase>
    inline bool Memory::IsInstanceOf(const TBase &e) {
        return dynamic_cast<T *>(&(e)) != NULL;
    }

    template<typename T, typename TBase>
    inline bool Memory::IsInstanceOf(TBase &e) {
        return dynamic_cast<T *>(&(e)) != NULL;
    }

    template<typename T, typename TBase>
    inline const T &Memory::GetInstanceOf(const TBase &e) {
        return (*dynamic_cast<const T *>(&(e)));
    }

    template<typename T, typename TBase>
    inline T &Memory::GetInstanceOf(TBase &e) {
        return (*dynamic_cast<T *>(&(e)));
    }

}