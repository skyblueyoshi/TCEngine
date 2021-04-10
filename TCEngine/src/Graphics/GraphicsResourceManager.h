#pragma once

#include <vector>
#include "GraphicsResource.h"

namespace Tce {

    template<class T>
    class GraphicsResourceManager : public GraphicsResource {
    public:
        GraphicsResourceManager(std::shared_ptr<GraphicsDevice> &pDevice)
                : GraphicsResource(pDevice) {}

        virtual ~GraphicsResourceManager() {
            m_elements.clear();
        }

        // 获取
        // @param id 着色器在管理器内的ID
        // @return 着色器指针
        inline std::shared_ptr<T> &Get(uint32_t id) {
            auto &p = _InnerGet(id);
            assert(p);
            return p;
        }

        // 加载资源
        // @param pElement 资源元素指针
        // @return 资源在管理器内的ID
        uint32_t Load(std::shared_ptr<T> &pElement) {
            assert(pElement);
            int id = _Add(pElement);
            pElement->SetID(id);
            return id;
        }

        // 卸载资源
        // @param id 资源在管理器内的ID
        void UnloadByID(uint32_t id) {
            auto &p = Get(id);
            if (p) Unload(p);
        }

        // 卸载全部资源
        void UnloadAll() {
            for (auto &p : m_elements) {
                if (p) Unload(p);
            }
        }

        // 卸载资源
        // @param id 资源在管理器内的ID
        virtual void Unload(std::shared_ptr<T> &pElement) {
            if (pElement) {
                _Remove(pElement->GetID());
            }
        }

    private:

        // 添加
        // @param pElement 资源元素指针
        // @return 资源在管理器内的ID
        uint32_t _Add(std::shared_ptr<T> &pElement) {
            assert(pElement);
            if (!m_freeIds.empty()) {
                auto id = m_freeIds[m_freeIds.size() - 1];
                m_freeIds.resize(m_freeIds.size() - 1);
                auto &p = Get(id);
                assert(p);
                p = pElement;
                return id;
            } else {
                return _InnerAdd(pElement);
            }
        }

        // 移除
        // @param id 资源在管理器内的ID
        void _Remove(uint32_t id) {
            auto &p = Get(id);
            if (p) {
                p = nullptr;
                m_freeIds.push_back(id);
            }
        }

        // 由ID获取元素
        inline std::shared_ptr<T> &_InnerGet(uint32_t id) {
            return m_elements.at(id - 1);
        }

        // 添加元素，返回新的ID
        inline uint32_t _InnerAdd(std::shared_ptr<T> &pElement) {
            m_elements.push_back(pElement);
            return m_elements.size();
        }

    protected:
        std::vector<std::shared_ptr<T>> m_elements;     // 元素表

    private:
        std::vector<uint32_t> m_freeIds;                // ID回收表
    };

}