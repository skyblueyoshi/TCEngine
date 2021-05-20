#pragma once

#include "GraphicsResource.h"

namespace Tce {

    class Shader : public GraphicsResource {
    public:
        // 着色器类型
        enum EnumStage {
            STAGE_VERTEX,
            STAGE_PIXEL
        };

        Shader() = default;

        // 构造函数
        // @param id 着色器在管理器中的ID
        // @param stage 着色器类型
        // @param code  着色器代码
        // @param handle 着色器句柄
        Shader(EnumStage stage, String code, uint32_t handle);

        virtual ~Shader() = default;

    private:
        EnumStage m_stage{};            // 当前着色器类型
        String m_code{};           // 着色器源码
    };

}