#pragma once

#include "IList.h"

namespace Tce {

    template <typename T>
    class ArrayList : public IList<T> {
    public:
        ArrayList() = default;
        virtual ~ArrayList() = default;
        ArrayList(size_t capacity) {
            _arr.reserve(capacity);
        }
        ArrayList(const ArrayList& arr) = default;
        ArrayList(ArrayList&& arr) = default;
        ArrayList(const std::vector<T>& v) : _arr(v) {}
        ArrayList(std::vector<T>&& v) : _arr(std::move(v)) {}
        ArrayList& operator=(const ArrayList& arr) {
            if (this != &arr) {
                _arr = arr._arr;
            }
            return *this;
        }
        ArrayList& operator=(ArrayList&& arr) {
            if (this != &arr) {
                _arr = std::move(arr._arr);
            }
            return *this;
        }
//        static ArrayList Repeat(const T& value, size_t count) {
//            ArrayList temp(count);
//            for (size_t i = 0; i < count; i++) temp.Add(value);
//            return std::move(temp);
//        }
        const T& operator[](size_t index) const {
            return GetAt(index);
        }
        T& operator[](size_t index) {
            return GetAt(index);
        }
        const T& GetAt(size_t index) const {
            return _arr.at(index);
        }
        T& GetAt(size_t index) {
            return _arr.at(index);
        }
        typename std::vector<T>::iterator begin() {
            return _arr.begin();
        }
        typename std::vector<T>::iterator end() {
            return _arr.end();
        }
        size_t Add(const T& value) {
            _arr.push_back(value);
            return _arr.size() - 1;
        }
        size_t EmAdd(T&& value) {
            _arr.emplace_back(std::move(value));
            return _arr.size() - 1;
        }
        void Insert(size_t index, const T& value) {
            _arr.insert(_arr.begin() + (int)index, value);
        }
        void EmInsert(size_t index, T&& value) {
            _arr.emplace(_arr.begin() + (int)index, value);
        }
        void Clear() {
            _arr.clear();
        }
        void FreeMemory() {
            std::vector<T> temp;
            _arr.swap(temp);
        }
        bool Empty() const {
            return Count() == 0;
        }
        size_t Count() const {
            return _arr.size();
        }

        virtual void SetCount(size_t count) {
            _arr.resize(count);
        }
        void SetCount(size_t count, const T& fill) {
            _arr.resize(count, fill);
        }
        size_t Capacity() const {
            return _arr.capacity();
        }
        void SetCapacity(size_t capacity) {
            return _arr.reserve(capacity);
        }
        void Swap(ArrayList & arr) {
            _arr.swap(arr._arr);
        }
//        int IndexOf(const T& value, size_t startIndex, size_t count, bool findLast) const {
//            size_t end = startIndex + count;
//            if (!findLast) {
//                for (size_t i = startIndex; i < end; i++)
//                    if (_arr.at(i) == value) return (int)i;
//            }
//            else {
//                for (size_t i = end - 1; i >= startIndex; i--)
//                    if (_arr.at(i) == value) return (int)i;
//            }
//            return -1;
//        }
//        int IndexOf(const T& value, size_t startIndex, size_t count) const {
//            return IndexOf(value, startIndex, count, false);
//        }
//        int IndexOf(const T& value, size_t startIndex) const {
//            return IndexOf(value, startIndex, Count() - startIndex);
//        }
//        int IndexOf(const T& value) const {
//            return IndexOf(value, 0);
//        }
//        int LastIndexOf(const T& value) const {
//            return IndexOf(value, 0, Count(), true);
//        }
//        int LastIndexOf(const T& value, int startIndex) const {
//            return IndexOf(value, startIndex, Count() - startIndex, true);
//        }
//        int LastIndexOf(const T& value, int startIndex, int count) const {
//            return IndexOf(value, startIndex, count, true);
//        }
//        bool Contains(const T& value) const {
//            return IndexOf(value) != -1;
//        }
//        void Remove(const T& value) {
//            int index = IndexOf(value);
//            if (index != -1) {
//                RemoveAt((size_t)index);
//            }
//        }
        void RemoveAt(size_t index) {
            _arr.erase(_arr.begin() + (int)index);
        }
        void RemoveBack() {
            _arr.pop_back();
        }
        const T* Data() const {
            return _arr.data();
        }
        T* Data() {
            return _arr.data();
        }

    protected:
        std::vector<T> _arr;
    };
}