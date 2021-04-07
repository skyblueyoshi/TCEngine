#pragma once

#include "GraphicsDevice.h"
#include <memory>

namespace Tce {

    class GraphicsDevice;

    class GraphicsResource {
    protected:
        std::weak_ptr<GraphicsDevice> m_pDevice;    // 设备指针
        bool m_enabled{};                           // 正在使用
    public:
        GraphicsResource() = default;
        GraphicsResource(std::shared_ptr<GraphicsDevice> & pDevice);
        virtual ~GraphicsResource();
        // 加载资源
        virtual void Load();
        // 卸载资源
        virtual void Unload();
    };

}
