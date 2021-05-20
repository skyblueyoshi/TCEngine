#pragma once

#include "TCUtils.h"

namespace Tce {

    class GraphicsDevice;

    // 渲染资源类
    class GraphicsResource {
    public:
        GraphicsResource() = default;

        GraphicsResource(uint32_t handle);

        GraphicsResource(GraphicsDevice* pDevice);

        virtual ~GraphicsResource() = default;

        // 设置可用
        // @param enabled 当前是否可用
        inline void SetEnabled(bool enabled) {
            m_enabled = enabled;
        }

        // 是否可用
        inline bool IsEnabled() const {
            return m_enabled;
        }

        // 写入ID
        // @param ID 在资源池中的ID
        inline void SetID(uint32_t id) {
            m_id = id;
        }

        // 获取ID
        // @return ID 在资源池中的ID
        inline uint32_t GetID() const {
            return m_id;
        }

        // 获取句柄
        // @return 句柄
        inline uint32_t GetHandle() const {
            return m_handle;
        }

    protected:
        GraphicsDevice* m_pDevice{nullptr};         // 设备指针
    private:
        uint32_t m_id{};                            // 在资源池中的ID
        uint32_t m_handle{};                        // 资源句柄
        bool m_enabled{};                           // 正在使用
    };

}
