#include "ProgramManager.h"

namespace Tce {

    ProgramManager::ProgramManager(std::shared_ptr<GraphicsDevice> pDevice)
            : GraphicsResourceManager<Program>(pDevice) {

    }

}