#pragma once

#include "GraphicsResourceManager.h"
#include "Program.h"

namespace Tce {

    class ProgramManager : public GraphicsResourceManager<Program> {
    public:
        ProgramManager(std::shared_ptr<GraphicsDevice> pDevice);
        virtual ~ProgramManager() = default;
    };

}