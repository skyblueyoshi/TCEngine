#pragma once

#include <string>
#include "GraphicsResource.h"

namespace Tce {

    class Shader : public GraphicsResource {
    public:
        // 着色器类型
        enum Stage {
            STAGE_VERTEX,
            STAGE_PIXEL
        };

        // 构造函数
        // @param stage 着色器类型
        // @param code  着色器代码
        Shader(std::shared_ptr<GraphicsDevice> & pDevice, Stage stage, std::string code);

        // 加载资源
        void Load();

        // 卸载资源
        void Unload();

        // 获取句柄
        uint32_t GetHandle();

    private:
        Stage m_stage{};            // 当前着色器类型
        std::string m_code{};       // 着色器源码
        uint32_t m_handle{};        // 着色器句柄
    };

}