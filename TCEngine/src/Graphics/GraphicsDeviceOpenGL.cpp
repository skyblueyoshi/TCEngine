#include "GraphicsDevice.h"
#include "TCLog.h"
#include "TCImage.h"
#include "TCString.h"

namespace Tce {

#if defined(GLES)

    void GraphicsDevice::ResourceHandle::Free() {
        auto pHandle = const_cast<GLuint *>(&m_handle);
        switch (m_eType) {
            case RESOURCE_TEXTURE:
                glDeleteTextures(1, pHandle);
                break;
            case RESOURCE_SHADER:
                if (glIsShader(m_handle)) {
                    glDeleteShader(m_handle);
                }
                break;
            case RESOURCE_BUFFER:
                glDeleteBuffers(1, pHandle);
                break;
            case RESOURCE_PROGRAM:
                if (glIsProgram(m_handle)) {
                    glDeleteProgram(m_handle);
                }
                break;
            case RESOURCE_FRAMEBUFFER:
                glDeleteFramebuffers(1, pHandle);
                break;
        }
    }

    void GraphicsDevice::_PlatformInit() {

        TCE_LOG_INFO("Android OpenGLES Start Initialize.");

        // GLES 初始化实现：
        // https://github.com/Apress/beg-android-cpp-game-dev/blob/master/Chapter5/Chapter5/jni/Framework/Renderer/Renderer.cpp
        // 谷歌官方源码参考：
        // https://github.com/android/ndk-samples/blob/master/native-activity/app/src/main/cpp/main.cpp

        // initialize OpenGL ES and EGL

        /*
         * Here specify the attributes of the desired configuration.
         * Below, we select an EGLConfig with at least 8 bits per color
         * component compatible with on-screen windows
         */
        const EGLint attribs[] =
                {
                        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                        EGL_BLUE_SIZE, 8,
                        EGL_GREEN_SIZE, 8,
                        EGL_RED_SIZE, 8,
                        EGL_NONE
                };

        EGLint format;
        EGLint numConfigs;
        EGLConfig config;

        m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(m_display, nullptr, nullptr);

        /* Here, the application chooses the configuration it desires. In this
         * sample, we have a very simplified selection process, where we pick
         * the first EGLConfig that matches our criteria */
        eglChooseConfig(m_display, attribs, &config, 1, &numConfigs);

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

        auto pAndroidState = m_pAppState->GetAndroidState();

        ANativeWindow_setBuffersGeometry(pAndroidState->window, 0, 0, format);

        m_surface = eglCreateWindowSurface(m_display, config, pAndroidState->window, nullptr);

        EGLint contextAttribs[] =
                {
                        EGL_CONTEXT_CLIENT_VERSION, 2,
                        EGL_NONE
                };
        m_context = eglCreateContext(m_display, config, nullptr, contextAttribs);

        eglMakeCurrent(m_display, m_surface, m_surface, m_context);

        EGLint width, height;
        eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width);
        eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height);
        m_width = width;
        m_height = height;

        // Check openGL on the system
        auto opengl_info = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
        for (auto name : opengl_info) {
            auto info = glGetString(name);
            TCE_LOG_INFO("OpenGL Info: %s", info);
        }

        // Initialize GL state.
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
        //glEnable(GL_CULL_FACE);
        //glShadeModel(GL_SMOOTH);

        // 使用深度检测
        glEnable(GL_DEPTH_TEST);
        // 接受离相机更近的片元
        glDepthFunc(GL_LESS);
        // 剔除不是面朝摄像机的三角形面
        glEnable(GL_CULL_FACE);

        TCE_LOG_INFO("Android OpenGLES Initialize Success!");
        TCE_LOG_INFO("Window size: %d x %d", m_width, m_height);

        glViewport(0, 0, m_width, m_height);
    }

    void GraphicsDevice::_PlatformDestroy() {

        if (m_display != EGL_NO_DISPLAY) {
            eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (m_context != EGL_NO_CONTEXT) {
                eglDestroyContext(m_display, m_context);
            }
            if (m_surface != EGL_NO_SURFACE) {
                eglDestroySurface(m_display, m_surface);
            }
            eglTerminate(m_display);

        }
        m_display = EGL_NO_DISPLAY;
        m_context = EGL_NO_CONTEXT;
        m_surface = EGL_NO_SURFACE;
    }

    bool GraphicsDevice::_PlatformCanRender() {
        return m_initialized;
    }

    void GraphicsDevice::_PlatformFixDevice() {

    }

    void GraphicsDevice::_PlatformClear(Color color) {
        auto vColor = color.ToVector4();
        glClearColor(vColor.x, vColor.y, vColor.z, vColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GraphicsDevice::_PlatformPresent() {
        eglSwapBuffers(m_display, m_surface);
    }

    std::shared_ptr<Texture> GraphicsDevice::_PlatformCreateTexture(const ImageData& data) {
        // 创建纹理
        uint32_t handle = 0;
        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);
        // 传入纹理
        glTexImage2D(GL_TEXTURE_2D,
                     0, GL_RGBA,
                     data.m_width, data.m_height,
                     0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data.m_data.Data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        return std::make_shared<Texture>(handle, data.m_width, data.m_height);
    }

    std::shared_ptr<Shader> GraphicsDevice::_PlatformCreateShader(Shader::EnumStage eStage, const String &code) {
        try {
            // 创建并获取着色器ID句柄
            GLuint handle = glCreateShader(
                    eStage == Shader::STAGE_VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

            // 编译着色器
            char const *pSourceCode = code.Data();
            glShaderSource(handle, 1, &pSourceCode, nullptr);
            glCompileShader(handle);

            GLint compileResult = GL_FALSE;
            int infoLogLength = 0;

            // 检测着色器
            glGetShaderiv(handle, GL_COMPILE_STATUS, &compileResult);
            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength) {
                std::string errorMessage;
                errorMessage.resize(infoLogLength);
                glGetShaderInfoLog(handle, infoLogLength, nullptr, &errorMessage[0]);
                TCE_LOG_ERROR("%s\n", &errorMessage[0]);
                throw std::runtime_error(errorMessage.c_str());
            }
            return std::make_shared<Shader>(eStage, code, handle);
        }
        catch (const std::exception &ex) {
            throw std::runtime_error(String::Format(
                    "Failed to load %s shader: \n%s",
                    (eStage == Shader::STAGE_VERTEX ? "vertex" : "pixel"),
                    ex.what()).Data());
        }
    }

    std::shared_ptr<Tce::Program> GraphicsDevice::_PlatformCreateProgram(const String &vertexCode, const String &pixelCode) {
        try {
            int vertexId = m_pShaderManager->LoadVertexShader(vertexCode);
            int pixelId = m_pShaderManager->LoadPixelShader(pixelCode);

            auto &pVertexShader = m_pShaderManager->Get(vertexId);
            auto &pPixelShader = m_pShaderManager->Get(pixelId);

            uint32_t handle = glCreateProgram();

            // 连接着色器
            glAttachShader(handle, pVertexShader->GetHandle());
            glAttachShader(handle, pPixelShader->GetHandle());
            glLinkProgram(handle);

            // 检查
            GLint result = GL_FALSE;
            int infoLogLength;
            glGetProgramiv(handle, GL_LINK_STATUS, &result);
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0) {
                std::string errorMessage;
                errorMessage.resize(infoLogLength);
                glGetProgramInfoLog(handle, infoLogLength, nullptr, &errorMessage[0]);
                TCE_LOG_ERROR("%s\n", &errorMessage[0]);
                throw std::runtime_error(errorMessage.c_str());
            }

            // 解除附着
            glDetachShader(handle, pVertexShader->GetHandle());
            glDetachShader(handle, pPixelShader->GetHandle());

            // 卸载着色器
            m_pShaderManager->UnloadByID(vertexId);
            m_pShaderManager->UnloadByID(pixelId);

            return std::make_shared<Program>(handle);
        }
        catch (const std::exception & ex) {
            throw std::runtime_error(String::Format(
                    "Failed to load shader program: \n%s",
                    ex.what()).Data());
        }
    }

#endif

}
