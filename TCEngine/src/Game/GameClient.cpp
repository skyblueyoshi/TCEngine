//
// Created by cn on 2021/4/3.
//

#include <Type/Matrix.h>
#include "GameClient.h"
#include "GraphicsDevice.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"

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
                           std::shared_ptr<GraphicsDevice> &pGraphicsDevice)
            : Game(false), m_pAppState(pAppState), m_pGraphicsDevice(pGraphicsDevice) {

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
            if (isCurrentLoopRender && m_pGraphicsDevice->CanRender()) {

                _MainRender();

                tickTemp.TimingLoopRender(m_state.framePreSecond, m_state.gameSpeed);
                tickTemp.CheckSleep(m_state.isMaxFps);
            } else {        //不满足渲染条件（设备丢失），修复设备
                m_pGraphicsDevice->FixDevice();
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
        m_pGraphicsDevice->Clear(Color(0, 0, 128));


        static const GLfloat g_vertex_buffer_data[] = {
                -1.0f, -1.0f, -1.0f, // triangle 1 : begin
                -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, // triangle 1 : end
                1.0f, 1.0f, -1.0f, // triangle 2 : begin
                -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f, // triangle 2 : end
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f
        };
        // One color for each vertex. They were generated randomly.
        static const GLfloat g_color_buffer_data[] = {
                0.583f, 0.771f, 0.014f,
                0.609f, 0.115f, 0.436f,
                0.327f, 0.483f, 0.844f,
                0.822f, 0.569f, 0.201f,
                0.435f, 0.602f, 0.223f,
                0.310f, 0.747f, 0.185f,
                0.597f, 0.770f, 0.761f,
                0.559f, 0.436f, 0.730f,
                0.359f, 0.583f, 0.152f,
                0.483f, 0.596f, 0.789f,
                0.559f, 0.861f, 0.639f,
                0.195f, 0.548f, 0.859f,
                0.014f, 0.184f, 0.576f,
                0.771f, 0.328f, 0.970f,
                0.406f, 0.615f, 0.116f,
                0.676f, 0.977f, 0.133f,
                0.971f, 0.572f, 0.833f,
                0.140f, 0.616f, 0.489f,
                0.997f, 0.513f, 0.064f,
                0.945f, 0.719f, 0.592f,
                0.543f, 0.021f, 0.978f,
                0.279f, 0.317f, 0.505f,
                0.167f, 0.620f, 0.077f,
                0.347f, 0.857f, 0.137f,
                0.055f, 0.953f, 0.042f,
                0.714f, 0.505f, 0.345f,
                0.783f, 0.290f, 0.734f,
                0.722f, 0.645f, 0.174f,
                0.302f, 0.455f, 0.848f,
                0.225f, 0.587f, 0.040f,
                0.517f, 0.713f, 0.338f,
                0.053f, 0.959f, 0.120f,
                0.393f, 0.621f, 0.362f,
                0.673f, 0.211f, 0.457f,
                0.820f, 0.883f, 0.371f,
                0.982f, 0.099f, 0.879f
        };
        // Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
        static const GLfloat g_uv_buffer_data[] = {
                0.000059f, 1.0f - 0.000004f,
                0.000103f, 1.0f - 0.336048f,
                0.335973f, 1.0f - 0.335903f,
                1.000023f, 1.0f - 0.000013f,
                0.667979f, 1.0f - 0.335851f,
                0.999958f, 1.0f - 0.336064f,
                0.667979f, 1.0f - 0.335851f,
                0.336024f, 1.0f - 0.671877f,
                0.667969f, 1.0f - 0.671889f,
                1.000023f, 1.0f - 0.000013f,
                0.668104f, 1.0f - 0.000013f,
                0.667979f, 1.0f - 0.335851f,
                0.000059f, 1.0f - 0.000004f,
                0.335973f, 1.0f - 0.335903f,
                0.336098f, 1.0f - 0.000071f,
                0.667979f, 1.0f - 0.335851f,
                0.335973f, 1.0f - 0.335903f,
                0.336024f, 1.0f - 0.671877f,
                1.000004f, 1.0f - 0.671847f,
                0.999958f, 1.0f - 0.336064f,
                0.667979f, 1.0f - 0.335851f,
                0.668104f, 1.0f - 0.000013f,
                0.335973f, 1.0f - 0.335903f,
                0.667979f, 1.0f - 0.335851f,
                0.335973f, 1.0f - 0.335903f,
                0.668104f, 1.0f - 0.000013f,
                0.336098f, 1.0f - 0.000071f,
                0.000103f, 1.0f - 0.336048f,
                0.000004f, 1.0f - 0.671870f,
                0.336024f, 1.0f - 0.671877f,
                0.000103f, 1.0f - 0.336048f,
                0.336024f, 1.0f - 0.671877f,
                0.335973f, 1.0f - 0.335903f,
                0.667969f, 1.0f - 0.671889f,
                1.000004f, 1.0f - 0.671847f,
                0.667979f, 1.0f - 0.335851f
        };
        static bool init = false;

        static GLuint vertexbuffer;
        static GLuint colorbuffer;
        static GLuint uvbuffer;

        static std::shared_ptr<Program> ppg;

        if (!init) {
            init = true;

            const std::string svs = "attribute vec3 vertexPosition_modelspace;\n"
                                    "attribute vec3 vertexColor;\n"
                                    "uniform mat4 MVP;\n"
                                    "varying vec3 fragmentColor;\n"
                                    "void main(){\n"
                                    "  fragmentColor = vertexColor;\n"
                                    "  gl_Position = MVP * vec4(vertexPosition_modelspace,1);\n"
                                    "}";
            const std::string sPS = "precision mediump float;\n"
                                    "varying vec3 fragmentColor;\n"
                                    "void main(){\n"
                                    "  gl_FragColor.xyz = fragmentColor;\n"
                                    "}";
            const std::string svs2 = "attribute vec3 vertexPosition_modelspace;\n"
                                     "attribute vec2 vertexUV;\n"
                                     "uniform mat4 MVP;\n"
                                     "varying vec2 UV;\n"
                                     "void main(){\n"
                                     "  UV = vertexUV;\n"
                                     "  gl_Position = MVP * vec4(vertexPosition_modelspace,1);\n"
                                     "}";
            const std::string sPS2 = "precision highp float;\n"
                                     "varying vec2 UV;\n"
                                     "uniform sampler2D myTextureSampler;\n"
                                     "void main(){\n"
                                     "  gl_FragColor = texture2D(myTextureSampler, UV);\n"
                                     "}";


            auto pProgramManager = m_pGraphicsDevice->GetProgramManager();
            ppg = pProgramManager->Get(pProgramManager->Load(svs2, sPS2));

            // This will identify our vertex buffer
// Generate 1 buffer, put the resulting identifier in vertexbuffer
            glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,
                         GL_STATIC_DRAW);


            glGenBuffers(1, &colorbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data,
                         GL_STATIC_DRAW);


            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data,
                         GL_STATIC_DRAW);


            auto pTextureManager = m_pGraphicsDevice->GetTextureManager();
            pTextureManager->LoadTextureFromFile("oo.png");
        }


        glUseProgram(ppg->GetHandle());

        static float dgg = 0;
        dgg += 1;
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(glm::radians(dgg), (float) 3 / (float) 3, 0.1f,
                                                100.0f);

// Or, for an ortho camera :
//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

// Camera matrix
        glm::mat4 View = glm::lookAt(
                glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

// Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model = glm::mat4(1.0f);
// Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP = Projection * View *
                        Model; // Remember, matrix multiplication is the other way around



        Matrix projection = Matrix::CreatePerspectiveFOV(
                glm::radians(45.0f),
                (float) m_pGraphicsDevice->GetDisplayWidth() /
                (float) m_pGraphicsDevice->GetDisplayHeight(),
                0.1f,
                100.0f);

        static float zz = -3;
        static float xx = 4;
        static float tt = 1;
        tt += 0.01;
        xx = sin(tt) * 4;
        zz = cos(tt) * 5;

        Matrix view = Matrix::CreateLookAt(
                Vector3(xx, 3, zz),
                Vector3(0, 0, 0),
                Vector3(0, 1, 0));

        Matrix model = Matrix::CreateIdentity();

        Matrix mvp = model * view * projection;

        auto matrixID = glGetUniformLocation(ppg->GetHandle(), "MVP");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp._11);
        //glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

        GLuint textureID = glGetUniformLocation(ppg->GetHandle(), "myTextureSampler");

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 1);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(textureID, 0);

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

        // 2nd attribute buffer : colors
//        glEnableVertexAttribArray(1);
//        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
//        glVertexAttribPointer(
//                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
//                3,                                // size
//                GL_FLOAT,                         // type
//                GL_FALSE,                         // normalized?
//                0,                                // stride
//                (void *) nullptr                          // array buffer offset
//        );

// 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                2,                                // size : U+V => 2
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void *) 0                          // array buffer offset
        );

// Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0,
                     3 * 12); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        m_pGraphicsDevice->Present();
    }

}

