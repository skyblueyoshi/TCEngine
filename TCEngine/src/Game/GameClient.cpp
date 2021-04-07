//
// Created by cn on 2021/4/3.
//

#include "GameClient.h"
#include "Graphics.h"


// 调试器注入检测
static bool _PebIsDebuggedApproach() {
#ifdef CHECK_DEBUGGER
    char result = 0;
    __asm
    {
        // 进程的PEB地址放在fs这个寄存器位置上
        mov eax, fs:[30h]
        // 查询BeingDebugged标志位
        mov al, BYTE PTR[eax + 2]
        mov result, al
    }
    return result != 0;
#else
    return false;
#endif
}

namespace Tce {
    GameClient::GameClient(std::shared_ptr<AppState> &pAppState,
                           std::shared_ptr<Graphics> &pGraphics)
            : Game(false), m_pAppState(pAppState), m_pGraphics(pGraphics) {

    }

    bool GameClient::Init() {
        return true;
    }

    // 主循环源码
    // https://dewitters.com/dewitters-gameloop/
    // 该循环算法优先确保更新逻辑执行次数正常，可牺牲渲染逻辑执行次数
    void GameClient::_DoMainLoop() {

        TickInGame tickTemp;
        bool isFirstLoopMsg = false;
        GameWindowMessage gameMessage{};
        while (m_isRunning) {

            // 客户端主循环

// 检测窗口是否置前
            _CheckWindowFront();

            bool isCurrentLoopChangeUpdater = _StateTrigger();
            if (m_state.state == GameState::STATE_EXITING) {
                m_isRunning = false;
                break;
            }

            if (_ProcessWindowMessage(gameMessage)) {
                isFirstLoopMsg = true;
            }

            bool isCurrentLoopRunUpdate = false;
            tickTemp.BeginLoopUpdate();
            while (tickTemp.CanLoopUpdate()) {

                //消息（一次主逻辑更新一一对应一次消息更新）
                if (!isFirstLoopMsg) {
                    _ProcessWindowMessage(gameMessage);
                }
                isFirstLoopMsg = false;
                isCurrentLoopRunUpdate = true;

                //主逻辑
                _MainUpdate();

                tickTemp.NextLoopUpdate();
            }
            tickTemp.EndLoopUpdate();

            bool isCurrentLoopRender = (!isCurrentLoopChangeUpdater) ||
                                       (isCurrentLoopChangeUpdater && isCurrentLoopRunUpdate);

            //主绘制
            if (isCurrentLoopRender && m_pGraphics->CanRender()) {

                _MainRender();

                tickTemp.TimingLoopRender(m_state.framePreSecond, m_state.gameSpeed);
                tickTemp.CheckSleep(m_state.isMaxFps);
            } else {        //不满足渲染条件（设备丢失），修复设备
                m_pGraphics->FixDevice();
                tickTemp = TickInGame();
            }

            //检测外部调试器注入
            if (_PebIsDebuggedApproach()) {
                // TODO 处理调试器注入
            }
        }
    }

    void GameClient::_MainRender() {
        Render();
    }

    void GameClient::_CheckWindowFront() {
#if defined(_WINDOWS)
        m_state.isFrontWindow = (GetForegroundWindow() == hwnd);
#endif

        //TODO 置前处理
//            pInputClient->SetEnabled(frontWindow);
//
//            //音乐处理
//            if (frontWindow) pMusicClient->ResumeMusic();
//            else pMusicClient->PauseMusic();
//
//            //音效处理
//            pSoundClient->SetEnabled(frontWindow);
    }

    bool GameClient::_ProcessWindowMessage(GameWindowMessage &gameMessage) {
#if defined(_WINDOWS)

#elif defined(__ANDROID__)
        int events;
        struct android_poll_source *pSource;
        int ident = ALooper_pollAll(0, nullptr, &events, (void **) &pSource);
        if (ident >= 0) {
            auto *pAndroidState = m_pAppState->GetAndroidState();
            if (pSource) {
                pSource->process(pAndroidState, pSource);
            }

            if (pAndroidState->destroyRequested) {
                m_state.SetState(GameState::STATE_EXITING);
            }
            return true;
        }
#endif
        return false;
    }

    void GameClient::Render() {
        m_pGraphics->Clear(Color(255, 255, 0));

        static const GLfloat g_vertex_buffer_data[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
        };
        static bool init = false;

        static GLuint vertexbuffer;

        if (!init) {
            init = true;
            // This will identify our vertex buffer
// Generate 1 buffer, put the resulting identifier in vertexbuffer
            glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,
                         GL_STATIC_DRAW);
        }

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void *) nullptr            // array buffer offset
        );
// Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);



        m_pGraphics->Present();
    }

}

