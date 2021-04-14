#pragma once

#if defined(_WINDOWS)
#   define DIRECTX
#else
#   define OPENGL
#   if defined(__ANDROID__)
#       define GLES

#   endif
#endif

#if defined(GLES)

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif

#include <src/Game/AppState.h>
#include <memory>
#include <list>
#include <mutex>
#include "ShaderManager.h"
#include "src/Type/Color.h"
#include "ProgramManager.h"
#include "TextureManager.h"

namespace Tce {

    class GraphicsResource;

    class GraphicsDevice {
    public:
        GraphicsDevice();

        virtual ~GraphicsDevice();

        // 初始化绘制设备
        // @param pAppState APP状态
        void Init(AppState* pAppState);

        // 销毁绘制设备
        void Destroy();

        // 判断当前设备状态是否允许绘制
        // @return 设备是否允许绘制
        bool CanRender();

        // 修复设备
        void FixDevice();

        // 清空设备
        void Clear(Color color);

        // 展示到屏幕
        void Present();

        // 获取着色器管理器
        ShaderManager* GetShaderManager() const;

        // 获取着色程序管理器
        ProgramManager* GetProgramManager() const;

        // 获取纹理管理器
        TextureManager* GetTextureManager() const;

        // 获取显示宽度
        // @return 显示宽度
        uint GetDisplayWidth() const;

        // 获取显示高度
        // @return 显示高度
        uint GetDisplayHeight() const;

        // 丢弃着色器
        // @param handle 着色器句柄
        void DisposeShader(uint32_t handle);

        // 丢弃着色程序
        // @param handle 着色程序句柄
        void DisposeProgram(uint32_t handle);

        // 丢弃纹理
        // @param handle 纹理句柄
        void DisposeTexture(uint32_t handle);

    private:
        void _PlatformInit();

        void _PlatformDestroy();

        bool _PlatformCanRender();

        void _PlatformFixDevice();

        void _PlatformClear(Color color);

        void _PlatformPresent();

    private:

        enum EnumResourceType {
            RESOURCE_TEXTURE,
            RESOURCE_SHADER,
            RESOURCE_BUFFER,
            RESOURCE_PROGRAM,
            RESOURCE_FRAMEBUFFER
        };

        struct ResourceHandle {
            EnumResourceType m_eType;
            uint32_t m_handle;

            static ResourceHandle Texture(uint32_t handle) {
                return ResourceHandle{RESOURCE_TEXTURE, handle};
            }

            static ResourceHandle Shader(uint32_t handle) {
                return ResourceHandle{RESOURCE_SHADER, handle};
            }

            static ResourceHandle Buffer(uint32_t handle) {
                return ResourceHandle{RESOURCE_BUFFER, handle};
            }

            static ResourceHandle Program(uint32_t handle) {
                return ResourceHandle{RESOURCE_PROGRAM, handle};
            }

            static ResourceHandle Framebuffer(uint32_t handle) {
                return ResourceHandle{RESOURCE_FRAMEBUFFER, handle};
            }

            void Free();
        };

        AppState* m_pAppState{nullptr};                 // APP状态
        uint m_width{};                                 // APP宽度
        uint m_height{};                                // APP高度
        uint64_t m_clearTimes{};                        // 设备清空次数
        bool m_initialized{};                           // 是否完成初始化
        std::list<ResourceHandle> m_nextDisposes;       // 下一帧丢弃资源表
        std::list<ResourceHandle> m_currentDisposes;    // 当前帧丢弃资源表
        std::mutex m_disposeLock;                       // 抛弃操作锁

        std::unique_ptr<ShaderManager> m_pShaderManager;     // 着色器管理器
        std::shared_ptr<ProgramManager> m_pProgramManager;   // 着色程序管理器
        std::shared_ptr<TextureManager> m_pTextureManager;   // 纹理管理器

#ifdef GLES
        EGLDisplay m_display{EGL_NO_DISPLAY};
        EGLContext m_context{EGL_NO_CONTEXT};
        EGLSurface m_surface{EGL_NO_SURFACE};
#endif
    };

}