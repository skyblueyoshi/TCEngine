#include "ShaderManager.h"
#include "GraphicsDevice.h"

namespace Tce {

    ShaderManager::ShaderManager(GraphicsDevice* pDevice)
            : GraphicsResourceManager<Shader>(pDevice) {

    }

    uint32_t ShaderManager::LoadVertexShader(const String &code) {
        return _LoadShader(Shader::STAGE_VERTEX, code);
    }

    uint32_t ShaderManager::LoadPixelShader(const String &code) {
        return _LoadShader(Shader::STAGE_PIXEL, code);
    }

    uint32_t ShaderManager::_LoadShader(Shader::EnumStage eStage, const String &code) {
        auto pShader = m_pDevice->CreateShader(eStage, code);
        return GraphicsResourceManager::Load(pShader);
    }

    void ShaderManager::Unload(std::shared_ptr<Shader> &pShader) {
        if (pShader) {
            m_pDevice->DisposeShader(pShader->GetHandle());
            GraphicsResourceManager::Unload(pShader);
        }
    }

}