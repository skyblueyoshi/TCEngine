#include <src/Utils/Log.h>
#include "GraphicsDevice.h"

namespace Tce {

    GraphicsDevice::GraphicsDevice() {

    }

    void GraphicsDevice::Init(std::shared_ptr<AppState> &pAppState) {
        if (!m_initialized) {
            m_pAppState = pAppState;
            _PlatformInit();
            m_initialized = true;
        }
    }

    void GraphicsDevice::Destroy() {
        if (m_initialized) {
            m_initialized = false;
            _PlatformDestroy();
        }
    }

    bool GraphicsDevice::CanRender() {
        return m_initialized && _PlatformCanRender();
    }

    void GraphicsDevice::FixDevice() {
        _PlatformFixDevice();
    }

    void GraphicsDevice::Clear(Color color) {
        _PlatformClear(color);
        m_clearTimes++;
    }

    void GraphicsDevice::Present() {
        _PlatformPresent();
    }
}
