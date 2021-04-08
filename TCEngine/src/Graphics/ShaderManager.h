#pragma once

#include "GraphicsResourceManager.h"
#include "Shader.h"

namespace Tce {

    class ShaderManager : public GraphicsResourceManager<Shader> {
    public:
        ShaderManager(std::shared_ptr<GraphicsDevice> pDevice);
        virtual ~ShaderManager() = default;
    };

}