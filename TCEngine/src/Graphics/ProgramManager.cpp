#include "ProgramManager.h"
#include "GraphicsDevice.h"
#include <utility>
#include <src/Utils/Log.h>
#include <src/Utils/StringHelper.h>

namespace Tce {

    ProgramManager::ProgramManager(std::shared_ptr<GraphicsDevice> &pDevice,
                                   std::shared_ptr<ShaderManager> &pShaderManager)
            : GraphicsResourceManager<Program>(pDevice), m_pShaderManager(pShaderManager) {

    }

    uint32_t ProgramManager::Load(const std::string &vertexCode, const std::string &pixelCode) {
        try {
            auto pShaderManager = m_pShaderManager.lock();
            int vertexId = pShaderManager->LoadVertexShader(vertexCode);
            int pixelId = pShaderManager->LoadPixelShader(pixelCode);

            auto &pVertexShader = pShaderManager->Get(vertexId);
            auto &pPixelShader = pShaderManager->Get(pixelId);

            uint32_t handle = glCreateProgram();

            // 连接着色器
            glAttachShader(handle, pVertexShader->GetHandle());
            glAttachShader(handle, pPixelShader->GetHandle());
            glLinkProgram(handle);

            // 检查
            GLint result = GL_FALSE;
            int infoLogLength;
            glGetProgramiv(handle, GL_LINK_STATUS, &result);
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0) {
                std::string errorMessage;
                errorMessage.resize(infoLogLength);
                glGetProgramInfoLog(handle, infoLogLength, nullptr, &errorMessage[0]);
                TCE_LOG_ERROR("%s\n", &errorMessage[0]);
                throw std::runtime_error(errorMessage.c_str());
            }

            // 解除附着
            glDetachShader(handle, pVertexShader->GetHandle());
            glDetachShader(handle, pPixelShader->GetHandle());

            // 卸载着色器
            pShaderManager->UnloadByID(vertexId);
            pShaderManager->UnloadByID(pixelId);

            auto pProgram = std::make_shared<Program>(handle);
            return GraphicsResourceManager::Load(pProgram);
        }
        catch (const std::exception & ex) {
            throw std::runtime_error(StringHelper::MakeFormat(
                    "Failed to load shader program: \n%s",
                    ex.what()).c_str());
        }
    }

    void ProgramManager::Unload(std::shared_ptr<Program> &pProgram) {
        if (pProgram) {
            m_pDevice.lock()->DisposeProgram(pProgram->GetHandle());
            GraphicsResourceManager::Unload(pProgram);
        }
    }

}