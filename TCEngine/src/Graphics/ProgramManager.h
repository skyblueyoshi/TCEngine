#pragma once

#include "GraphicsResourceManager.h"
#include "Program.h"

namespace Tce {
    class ShaderManager;
    class ProgramManager : public GraphicsResourceManager<Program> {
    public:
        ProgramManager(GraphicsDevice* pDevice, ShaderManager* pShaderManager);

        virtual ~ProgramManager() = default;

        // 加载着色程序
        // @param vertexCode 顶点着色器代码
        // @param pixelCode 像素着色器代码
        // @return ID
        uint32_t Load(const std::string &vertexCode, const std::string &pixelCode);

        // 卸载着色程序
        // @param pProgram 着色程序指针
        void Unload(std::shared_ptr<Program> & pProgram);

    private:
        ShaderManager* m_pShaderManager{nullptr};
    };

}