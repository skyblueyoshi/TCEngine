#include "GraphicsDevice.h"
#include "TCLog.h"
#include "TCImage.h"

namespace Tce {

    GraphicsDevice::GraphicsDevice() {
        if (!m_pShaderManager) {
            m_pShaderManager = std::make_unique<ShaderManager>(this);
        }
        if (!m_pProgramManager) {
            m_pProgramManager = std::make_unique<ProgramManager>(this, m_pShaderManager.get());
        }
        if (!m_pTextureManager) {
            m_pTextureManager = std::make_unique<TextureManager>(this);
        }
    }

    GraphicsDevice::~GraphicsDevice() {
        m_pShaderManager.reset();
        m_pProgramManager.reset();
        m_pTextureManager.reset();
    }

    void GraphicsDevice::Init(AppState* pAppState) {
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

    void GraphicsDevice::DisposeTexture(uint32_t handle) {
        std::lock_guard<std::mutex> lockGuard(m_disposeLock);
        m_nextDisposes.push_back(ResourceHandle::Texture(handle));
    }

    ShaderManager* GraphicsDevice::GetShaderManager() const {
        return m_pShaderManager.get();
    }

    ProgramManager* GraphicsDevice::GetProgramManager() const {
        return m_pProgramManager.get();
    }

    TextureManager* GraphicsDevice::GetTextureManager() const {
        return m_pTextureManager.get();
    }

    std::shared_ptr<Texture> GraphicsDevice::CreateTextureFromFile(const String &path) {
        ImageData imgData = Image::LoadPngFromFile(path);
        return _PlatformCreateTexture(imgData);
    }

    std::shared_ptr<Shader> GraphicsDevice::CreateShader(Shader::EnumStage eStage, const String &code) {
        return _PlatformCreateShader(eStage, code);
    }

    std::shared_ptr<Program> GraphicsDevice::CreateProgram(const String &vertexCode, const String &pixelCode) {
        return _PlatformCreateProgram(vertexCode, pixelCode);
    }
}
