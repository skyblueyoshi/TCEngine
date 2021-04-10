#include <src/Utils/Log.h>
#include "GraphicsDevice.h"

namespace Tce {

    GraphicsDevice::GraphicsDevice() {

    }

    GraphicsDevice::~GraphicsDevice() {
        m_shaderManager.reset();
    }

    void GraphicsDevice::InitAllManagers() {
        auto pGraphicsDevice = shared_from_this();
        if (!m_shaderManager) {
            m_shaderManager = std::make_shared<ShaderManager>(pGraphicsDevice);
        }
        if (!m_programManager) {
            m_programManager = std::make_shared<ProgramManager>(pGraphicsDevice, m_shaderManager);
        }
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

        // 丢弃当前资源
        for (auto &disposeElement : m_currentDisposes) {
            disposeElement.Free();
        }
        m_currentDisposes.clear();
        {
            // 将下次丢弃资源变成当前资源
            std::lock_guard<std::mutex> lockGuard(m_disposeLock);
            m_currentDisposes.swap(m_nextDisposes);
        }
    }

    void GraphicsDevice::DisposeShader(uint32_t handle) {
        std::lock_guard<std::mutex> lockGuard(m_disposeLock);
        m_nextDisposes.push_back(ResourceHandle::Shader(handle));
    }

    void GraphicsDevice::DisposeProgram(uint32_t handle) {
        std::lock_guard<std::mutex> lockGuard(m_disposeLock);
        m_nextDisposes.push_back(ResourceHandle::Program(handle));
    }

    std::shared_ptr<ShaderManager> &GraphicsDevice::GetShaderManager() {
        return m_shaderManager;
    }

    std::shared_ptr<ProgramManager> &GraphicsDevice::GetProgramManager() {
        return m_programManager;
    }
}
