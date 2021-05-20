#include "Shader.h"

namespace Tce {

    Shader::Shader(Shader::EnumStage stage, String code, uint32_t handle)
            : GraphicsResource(handle), m_stage(stage), m_code(std::move(code)) {}
}