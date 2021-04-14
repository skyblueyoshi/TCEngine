#include <src/Utils/StringHelper.h>
#include <GLES2/gl2.h>
#include "ShaderManager.h"
#include <src/Utils/Log.h>
#include "GraphicsDevice.h"

namespace Tce {

    ShaderManager::ShaderManager(GraphicsDevice* pDevice)
            : GraphicsResourceManager<Shader>(pDevice) {

    }

    uint32_t ShaderManager::LoadVertexShader(const std::string &code) {
        return _LoadShader(Shader::STAGE_VERTEX, code);
    }

    uint32_t ShaderManager::LoadPixelShader(const std::string &code) {
        return _LoadShader(Shader::STAGE_PIXEL, code);
    }

    uint32_t ShaderManager::_LoadShader(Shader::EnumStage eStage, const std::string &code) {
        try {
            // 创建并获取着色器ID句柄
            GLuint handle = glCreateShader(
                    eStage == Shader::STAGE_VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

            // 编译着色器
            char const *pSourceCode = code.c_str();
            glShaderSource(handle, 1, &pSourceCode, nullptr);
            glCompileShader(handle);

            GLint compileResult = GL_FALSE;
            int infoLogLength = 0;

            // 检测着色器
            glGetShaderiv(handle, GL_COMPILE_STATUS, &compileResult);
            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength) {
                std::string errorMessage;
                errorMessage.resize(infoLogLength);
                glGetShaderInfoLog(handle, infoLogLength, nullptr, &errorMessage[0]);
                TCE_LOG_ERROR("%s\n", &errorMessage[0]);
                throw std::runtime_error(errorMessage.c_str());
            }
            auto pShader = std::make_shared<Shader>(eStage, code, handle);
            return GraphicsResourceManager::Load(pShader);
        }
        catch (const std::exception &ex) {
            throw std::runtime_error(StringHelper::MakeFormat(
                    "Failed to load %s shader: \n%s",
                    (eStage == Shader::STAGE_VERTEX ? "vertex" : "pixel"),
                    ex.what()).c_str());
        }
    }

    void ShaderManager::Unload(std::shared_ptr<Shader> &pShader) {
        if (pShader) {
            m_pDevice->DisposeShader(pShader->GetHandle());
            GraphicsResourceManager::Unload(pShader);
        }
    }

}