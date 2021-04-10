#pragma once

#include <string>
#include "GraphicsResource.h"

namespace Tce {

    class Shader : public GraphicsResource {
    public:
        // 着色器类型
        enum EnumStage {
            STAGE_VERTEX,
            STAGE_PIXEL
        };

        // 构造函数
        // @param id 着色器在管理器中的ID
        // @param stage 着色器类型
        // @param code  着色器代码
        // @param handle 着色器句柄
        Shader(EnumStage stage, std::string code, uint32_t handle);

        virtual ~Shader() = default;

    private:
        EnumStage m_stage{};            // 当前着色器类型
        std::string m_code{};           // 着色器源码
    };

}