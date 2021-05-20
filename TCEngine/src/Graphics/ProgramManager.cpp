#include "ProgramManager.h"
#include "GraphicsDevice.h"

namespace Tce {

    ProgramManager::ProgramManager(GraphicsDevice* pDevice, ShaderManager* pShaderManager)
            : GraphicsResourceManager<Program>(pDevice), m_pShaderManager(pShaderManager) {

    }

    uint32_t ProgramManager::Load(const String &vertexCode, const String &pixelCode) {
        auto pProgram = m_pDevice->CreateProgram(vertexCode, pixelCode);
        return GraphicsResourceManager::Load(pProgram);
    }

    void ProgramManager::Unload(std::shared_ptr<Program> &pProgram) {
        if (pProgram) {
            m_pDevice->DisposeProgram(pProgram->GetHandle());
            GraphicsResourceManager::Unload(pProgram);
        }
    }

}