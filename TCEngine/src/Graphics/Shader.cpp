#include "Shader.h"
#include <utility>
#include <vector>
#include <Utils/Log.h>
#include "GraphicsDevice.h"

namespace Tce {

    Shader::Shader(Shader::EnumStage stage, std::string code, uint32_t handle)
            : GraphicsResource(handle), m_stage(stage), m_code(std::move(code)) {}
}