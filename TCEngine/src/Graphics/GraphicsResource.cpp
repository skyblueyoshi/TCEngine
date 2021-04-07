#include "GraphicsResource.h"
#include "GraphicsDevice.h"

namespace Tce {
    GraphicsResource::GraphicsResource(std::shared_ptr<GraphicsDevice> & pDevice)
    : m_pDevice(pDevice) {

    }

    GraphicsResource::~GraphicsResource() {
        Unload();
    }

    void GraphicsResource::Load() {
        m_enabled = true;
    }

    void GraphicsResource::Unload() {
        m_enabled = false;
    }
}

