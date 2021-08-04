#pragma once

#include "TCUtils.h"

namespace Tce {

    template <typename T, size_t TSIZE>
    class Array {
    public:
        Array() = default;
        Array(const Array& arr) = default;
        Array(Array&& arr) = default;
        virtual ~Array() = default;
        const T& operator[](size_t index) const {
            return _arr.at(index);
        }
        T& operator[](size_t index) {
            return _arr.at(index);
        }
        const T& GetAt(size_t index) const {
            return _arr.at(index);
        }
        T& GetAt(size_t index) {
            return _arr.at(index);
        }
        size_t Count() const {
            return TSIZE;
        }
        typename std::array<T, TSIZE>::iterator begin() {
            return _arr.begin();
        }
        typename std::array<T, TSIZE>::iterator end() {
            return _arr.end();
        }
        typename std::array<T, TSIZE>::const_iterator begin() const {
            return _arr.begin();
        }
        typename std::array<T, TSIZE>::const_iterator end() const {
            return _arr.end();
        }
        void Swap(Array & arr) {
            _arr.swap(arr._arr);
        }
        void Clear() {
            for (size_t i = 0; i < TSIZE; i++) {
                RemoveAt(i);
            }
        }
        int IndexOf(const T& value, size_t startIndex, size_t count, bool findLast) const {
            size_t end = startIndex + count;
            if (!findLast) {
                for (size_t i = startIndex; i < end; i++)
                    if (_arr.at(i) == value) return (int)i;
            }
            else {
                for (size_t i = end - 1; i >= startIndex; i--)
                    if (_arr.at(i) == value) return (int)i;
            }
            return -1;
        }
        int IndexOf(const T& value, size_t startIndex, size_t count) const {
            return IndexOf(value, startIndex, count, false);
        }
        int IndexOf(const T& value, size_t startIndex) const {
            return IndexOf(value, startIndex, Count() - startIndex);
        }
        int IndexOf(const T& value) const {
            return IndexOf(value, 0);
        }
        int LastIndexOf(const T& value) const {
            return IndexOf(value, 0, Count(), true);
        }
        int LastIndexOf(const T& value, int startIndex) const {
            return IndexOf(value, startIndex, Count() - startIndex, true);
        }
        int LastIndexOf(const T& value, int startIndex, int count) const {
            return IndexOf(value, startIndex, count, true);
        }
        bool Contains(const T& value) const {
            return IndexOf(value) != -1;
        }
        bool Remove(const T& value) {
            int index = IndexOf(value);
            if (index != -1) {
                RemoveAt(index);
                return true;
            }
            return false;
        }
        void RemoveAt(size_t index) {
            GetAt(index).~T();
            ::new (&GetAt(index)) T();
        }
        const T* Data() const {
            return _arr.data();
        }
        T* Data() {
            return _arr.data();
        }

    protected:
        std::array<T, TSIZE> _arr;
    };
}