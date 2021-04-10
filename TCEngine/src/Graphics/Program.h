#pragma once

#include "GraphicsResource.h"
#include "Shader.h"

namespace Tce {

    // 着色程序
    class Program : public GraphicsResource {
    public:
        Program(uint32_t handle);
        virtual ~Program() = default;

    };

}