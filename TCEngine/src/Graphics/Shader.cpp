#include "Shader.h"
#include <utility>
#include <vector>
#include <src/Utils/Log.h>
#include "GraphicsDevice.h"

namespace Tce {

    Shader::Shader(std::shared_ptr<GraphicsDevice> pDevice, Shader::Stage stage,
                   std::string code)
            : GraphicsResource(pDevice), m_stage(stage), m_code(std::move(code)) {

    }

    Shader::~Shader() {
        Shader::Unload();
    }

    void Shader::Load() {
        if (!IsEnabled()) {
            // 创建并获取着色器ID句柄
            m_handle = glCreateShader(
                    m_stage == STAGE_VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

            // 编译着色器
            char const *pSourceCode = m_code.c_str();
            glShaderSource(m_handle, 1, &pSourceCode, nullptr);
            glCompileShader(m_handle);

            GLint compileResult = GL_FALSE;
            int infoLogLength = 0;

            // 检测着色器
            glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compileResult);
            glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength) {
                std::string errorMessage;
                errorMessage.resize(infoLogLength);
                glGetShaderInfoLog(m_handle, infoLogLength, nullptr, &errorMessage[0]);
                TCE_LOG_ERROR("%s\n", &errorMessage[0]);
                throw std::exception();
            }
            GraphicsResource::Load();
        }
    }

    void Shader::Unload() {
        if (IsEnabled()) {
            m_pDevice.lock()->DisposeShader(m_handle);
            GraphicsResource::Unload();
        }
    }
}