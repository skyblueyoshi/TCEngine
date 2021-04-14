#include "GraphicsResource.h"
#include "GraphicsDevice.h"

namespace Tce {
    GraphicsResource::GraphicsResource(GraphicsDevice* pDevice)
    : m_pDevice(pDevice) {}

    GraphicsResource::GraphicsResource(uint32_t handle) : m_handle(handle) {

    }

}

