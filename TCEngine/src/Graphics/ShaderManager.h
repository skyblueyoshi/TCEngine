#pragma once

#include "GraphicsResourceManager.h"
#include "Shader.h"

namespace Tce {

    class ShaderManager : public GraphicsResourceManager<Shader> {
    public:
        ShaderManager(GraphicsDevice* pDevice);

        virtual ~ShaderManager() = default;

        // 加载顶点着色器，返回着色器在管理器的ID
        // @param code 顶点着色器代码
        // @return ID
        uint32_t LoadVertexShader(const std::string &code);

        // 加载像素着色器，返回着色器在管理器的ID
        // @param code 顶点着色器代码
        // @return ID
        uint32_t LoadPixelShader(const std::string &code);

        // 卸载并清除指定着色器
        // @param pShader 着色器指针
        void Unload(std::shared_ptr<Shader> & pShader);

    private:

        // 加载着色器，返回着色器在管理器的ID
        // @param eStage 着色器类型
        // @param code 顶点着色器代码
        // @return ID
        uint32_t _LoadShader(Shader::EnumStage eStage, const std::string &code);
    };

}