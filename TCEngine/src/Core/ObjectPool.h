
#pragma once

#include <array>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <new>
#include <type_traits>
#include <vector>
#include <list>
#include <assert.h>
#include "Memory.h"

namespace Tce {

    // 对象池
    // 简单的内存池实现
    template<typename T>
    class ObjectPool {
    public:
        // 对象池单个缓冲区能容纳的对象数量
        static constexpr size_t kCount = 2;// 128;

        ObjectPool() = default;

        ObjectPool(const ObjectPool &) = delete;

        ~ObjectPool() {
            for (auto &p : m_buffers) {
                SafeDelete(p);
            }
            m_buffers.clear();
        }

        // 在对象池中增加对象
        // @param obj 拷贝构造对象
        // @return 对象指针
        T *Add(const T &obj) {
            auto *pObject = _CreateEmpty();
            new(pObject) T(obj);
            return pObject;
        }

        // 在对象池中移动增加对象
        // @param obj 移动构造对象
        // @return 对象指针
        T *EmAdd(T &&obj) {
            auto *pObject = _CreateEmpty();
            new(pObject) T(std::move(obj));
            return pObject;
        }

        // 在对象池中移除对象
        // @param pObject 待移除的对象指针
        void Remove(T *pObject) {
            if (std::is_trivially_destructible<T>())
                pObject->~T();
            m_frees.push_back(pObject);
            assert(m_totals > 0);
            m_totals--;
            assert(m_frees.size() + m_totals == kCount * m_buffers.size());
        }

    private:

        // 创建一个空对象内存
        T *_CreateEmpty() {
            if (m_frees.empty())
                _AddBuffer();
            auto *pObject = m_frees.back();
            m_frees.pop_back();
            m_totals++;
            assert(m_frees.size() + m_totals == kCount * m_buffers.size());
            return pObject;
        }

        // 增加对象池缓冲区
        void _AddBuffer() {
            auto *pBuffer = new Buffer();
            m_buffers.emplace_back(pBuffer);
            auto *p = reinterpret_cast<T *>(pBuffer);
            p += kCount - 1;
            for (size_t i = kCount; i > 0; i--, p--)
                m_frees.push_back(p);
        }

        struct Buffer {
            alignas(T) std::array<uint8_t, sizeof(T) * kCount> buffer;
        };
        std::vector<Buffer *> m_buffers;                        // 缓冲区列表
        std::vector<T *> m_frees;                           // 可用列表
        size_t m_totals{};
    };
}