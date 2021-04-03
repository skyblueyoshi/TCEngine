
#include <exception>
#include "Game.h"
#include "Log.h"

#define GET_SERVER_CLIENT_NAME(isServer) (isServer ? "Server" : "Client")

// 调试器注入检测
static bool PebIsDebuggedApproach() {
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

    Tce::Game::Game(bool isServer) : m_isServer(isServer) {

    }

    bool Game::Init() {
        return true;
    }

    void Game::Run() {
        try {
            m_isRunning = true;
            _DoMainLoop();
            // TODO 卸载环境
        }
        catch (const std::exception &ex) {
            TCE_LOG_ERROR("%s runtime error.\n%s",
                    GET_SERVER_CLIENT_NAME(m_isServer), ex.what());
        }
    }

    // 主循环源码
    // https://dewitters.com/dewitters-gameloop/
    // 该循环算法优先确保更新逻辑执行次数正常，可牺牲渲染逻辑执行次数
    void Game::_DoMainLoop() {
        const int FRAMES_PER_SECOND = 60;		//游戏逻辑每秒处理次数
        const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;		//游戏逻辑恒定更新速率
        const int MAX_FRAMESKIP = 5;		//最大单次跳帧的次数，超过该次数就必须绘制新的图像

        MSG msg = {};
        ULONGLONG currentTick = TickTime::GetCurrentTickCount();		//当前帧计时器
        ULONGLONG nextGameTick = currentTick;		//下一次游戏更新计时器
        ULONGLONG nextFrameTick = currentTick;		//下一次帧绘制计时器
        ULONGLONG lastSecondGameTick = currentTick;		//上一秒游戏更新计时器
        ULONGLONG lastSecondFrameTick = currentTick;		//上一帧绘制计时器
        int frameIndexInCurrentSecond = 0;		//当前秒绘制累积器
        int updateIndexInCurrentSecond = 0;		//当前秒更新累积器
        DWORD sleepTime = 0;		//休眠时间
        int loops = 0;		//跳帧内次数
        bool isFirstLoopMsg = false;
        bool frontWindow = false;
        while (isRunning) {

            //发现外挂就自杀
            if (KILL_PROGRAM) {
                KillSelf();
            }

            frontWindow = (GetForegroundWindow() == hwnd);
            pInputClient->SetEnabled(frontWindow);

            //音乐处理
            if (frontWindow) pMusicClient->ResumeMusic();
            else pMusicClient->PauseMusic();

            //音效处理
            pSoundClient->SetEnabled(frontWindow);

            bool isCurrentLoopChangeUpdater = StateTrigger();
            if (clientConfiguration.state == CS_EXITING) {
                isRunning = false;
                break;
            }

            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                isFirstLoopMsg = true;
            }

            loops = 0;

            bool isCurrentLoopRunUpdate = false;

            while (TickTime::GetCurrentTickCount() > nextGameTick && loops < MAX_FRAMESKIP) {

                //消息（一次主逻辑更新一一对应一次消息更新）
                if (!isFirstLoopMsg) {
                    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
                isFirstLoopMsg = false;

                isCurrentLoopRunUpdate = true;

                //主逻辑
                MainUpdate();
                updateIndexInCurrentSecond++;
                nextGameTick += SKIP_TICKS;
                loops++;
            }
            nextGameTick = TickTime::GetCurrentTickCount();

            bool isCurrentLoopRender = (!isCurrentLoopChangeUpdater) || (isCurrentLoopChangeUpdater && isCurrentLoopRunUpdate);

            //主绘制
            if (isCurrentLoopRender && pDX->GetDeviceState() == D3D_OK && !pDX->IsReset()) {		//GetForegroundWindow() == hwnd &&

                MainRender();
                frameIndexInCurrentSecond++;

                nextFrameTick += SKIP_TICKS;
                currentTick = TickTime::GetCurrentTickCount();

                if (currentTick - lastSecondFrameTick > 1000) {		//绘制累积达到1s
                    lastSecondFrameTick = currentTick;		//更新上一秒绘制的tick
                    clientConfiguration.framePreSecond = frameIndexInCurrentSecond;		//更新FPS
                    frameIndexInCurrentSecond = 0;		//清空累积器
                }
                if (currentTick - lastSecondGameTick > 1000) {		//更新累积达到1s
                    lastSecondGameTick = currentTick;		//更新上一秒更新的tick
                    clientConfiguration.gameSpeed = updateIndexInCurrentSecond;		//更新游戏速率
                    updateIndexInCurrentSecond = 0;		//清空累积器
                }

                if (nextFrameTick >= currentTick) {
                    if (!clientConfiguration.isMaxFps) {		//休眠指定时间
                        sleepTime = DWORD(nextFrameTick - currentTick);
                        Sleep(sleepTime);
                    }
                }
                else {
                    //出现了延迟，不进行休眠
                }
            }
            else {		//不满足渲染条件（设备丢失），修复设备
                bool b1 = pDX->GetDeviceState() == D3DERR_DEVICENOTRESET;
                bool b2 = pDX->IsReset();
                if (b1 || b2) {
                    pDX->Reset();
                }
                currentTick = TickTime::GetCurrentTickCount();
                nextGameTick = currentTick;
                nextFrameTick = currentTick;
                lastSecondGameTick = currentTick;
                lastSecondFrameTick = currentTick;
                frameIndexInCurrentSecond = 0;
                updateIndexInCurrentSecond = 0;
                sleepTime = 0;
                loops = 0;
            }

            //检测外部调试器注入
            if (PebIsDebuggedApproach()) {
                // TODO 处理调试器注入
            }
        }
    }
}
