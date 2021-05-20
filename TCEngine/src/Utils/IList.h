#pragma once

#include "TCUtils.h"

namespace Tce {

    template <typename T>
    class IList : public TCObject {
    public:
        virtual size_t Add(const T& value) = 0;
        virtual size_t EmAdd(T&& value) = 0;
        virtual size_t Count() const = 0;
        virtual bool Empty() const = 0;
        virtual void Clear() = 0;
        virtual void FreeMemory() = 0;
        //virtual bool Contains(const T& value) const = 0;
        //virtual int IndexOf(const T& value) const = 0;
        virtual void Insert(size_t index, const T& value) = 0;
        virtual void EmInsert(size_t index, T&& value) = 0;
        //virtual void Remove(const T& value) = 0;
        virtual void RemoveAt(size_t index) = 0;
    };

}