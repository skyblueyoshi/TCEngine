#pragma once

#include <vector>
#include "GraphicsResource.h"

namespace Tce {

    template <class T>
    class GraphicsResourceManager : public GraphicsResource {
    public:
        GraphicsResourceManager(std::shared_ptr<GraphicsDevice> &pDevice)
            : GraphicsResource(pDevice) {}

        virtual ~GraphicsResourceManager() = default;

        // 获取
        // @param id 着色器在管理器内的ID
        // @return 着色器指针
        inline std::shared_ptr<T> & Get(uint32_t id) {
            auto &p = m_elements.at(id);
            assert(p);
            return p;
        }

        // 添加
        // @param pShader 着色器指针
        // @return 着色器在管理器内的ID
        uint32_t Add(std::shared_ptr<T> &pElement) {
            if (!m_frees.empty()) {
                auto id = m_frees[m_frees.size() - 1];
                m_frees.resize(m_frees.size() - 1);
                auto p = Get(id);
                assert(p);
                p = pElement;
                return id;
            } else {
                m_elements.push_back(pElement);
                return m_elements.size() - 1;
            }
        }

        // 移除
        // @param id 着色器在管理器内的ID
        void Remove(uint32_t id) {
            auto p = Get(id);
            if (p) {
                p = nullptr;
                m_frees.push_back(id);
            }
        }

    private:
        std::vector<std::shared_ptr<T>> m_elements;
        std::vector<uint32_t> m_frees;
    };

}