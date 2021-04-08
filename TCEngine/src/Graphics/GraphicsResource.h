#pragma once

#include <memory>

namespace Tce {

    class GraphicsDevice;

    // 渲染资源类
    class GraphicsResource {
    public:
        GraphicsResource() = default;

        GraphicsResource(std::shared_ptr<GraphicsDevice> &pDevice);

        virtual ~GraphicsResource();

        // 加载资源
        virtual void Load();

        // 卸载资源
        virtual void Unload();

        // 是否正在使用
        inline bool IsEnabled() const { return m_enabled; }

    protected:
        std::weak_ptr<GraphicsDevice> m_pDevice;    // 设备指针
    private:
        bool m_enabled{};                           // 正在使用
    };

}
