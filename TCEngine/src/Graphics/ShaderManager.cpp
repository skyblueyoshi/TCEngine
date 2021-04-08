#include "ShaderManager.h"

namespace Tce {

    ShaderManager::ShaderManager(std::shared_ptr<GraphicsDevice> pDevice)
            : GraphicsResourceManager<Shader>(pDevice) {

    }

}