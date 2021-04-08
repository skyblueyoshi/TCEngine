#include <src/Utils/Log.h>
#include "Program.h"
#include "GraphicsDevice.h"

namespace Tce {


    Program::Program(std::shared_ptr<GraphicsDevice> pDevice,
                     std::shared_ptr<Shader> &pVertexShader,
                     std::shared_ptr<Shader> &pPixelShader)
            : GraphicsResource(pDevice), m_pVertexShader(pVertexShader),
              m_pPixelShader(pPixelShader) {

    }

    Program::~Program() {
        Program::Unload();
    }

    void Program::Load() {
        if (!IsEnabled()) {
            assert(!m_pVertexShader->IsEnabled());
            assert(!m_pPixelShader->IsEnabled());

            m_pVertexShader->Load();
            m_pPixelShader->Load();

            m_handle = glCreateProgram();

            // 连接着色器
            glAttachShader(m_handle, m_pVertexShader->GetHandle());
            glAttachShader(m_handle, m_pPixelShader->GetHandle());
            glLinkProgram(m_handle);

            // 检查
            GLint result = GL_FALSE;
            int infoLogLength;
            glGetProgramiv(m_handle, GL_LINK_STATUS, &result);
            glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
            if ( infoLogLength > 0 ){
                std::string errorMessage;
                errorMessage.resize(infoLogLength);
                glGetProgramInfoLog(m_handle, infoLogLength, nullptr, &errorMessage[0]);
                TCE_LOG_ERROR("%s\n", &errorMessage[0]);
                throw std::exception();
            }

            // 解除附着
            glDetachShader(m_handle, m_pVertexShader->GetHandle());
            glDetachShader(m_handle, m_pPixelShader->GetHandle());

            // 卸载着色器
            m_pVertexShader->Unload();
            m_pPixelShader->Unload();

            GraphicsResource::Load();
        }
    }

    void Program::Unload() {
        if (IsEnabled()) {
            m_pDevice.lock()->DisposeProgram(m_handle);
            GraphicsResource::Unload();
        }
    }
}