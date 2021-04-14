#include "GraphicsDevice.h"
#include <src/Utils/Log.h>

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

#endif

}
