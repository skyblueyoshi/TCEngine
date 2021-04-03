
#include <exception>
#include "Game.h"
#include "../Utils/Log.h"
#include "../Utils/TickRunner.h"

#define GET_SERVER_CLIENT_NAME(isServer) (isServer ? "Server" : "Client")

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

    struct TickTemp {
        uint64_t currentTick{TickRunner::GetCurrentTickCount()};		//当前帧计时器
        uint64_t nextGameTick{currentTick};		                        //下一次游戏更新计时器
        uint64_t nextFrameTick{currentTick};		                    //下一次帧绘制计时器
        uint64_t lastSecondGameTick{currentTick};		                //上一秒游戏更新计时器
        uint64_t lastSecondFrameTick{currentTick};		                //上一帧绘制计时器
        int frameIndexInCurrentSecond{};	                        	//当前秒绘制累积器
        int updateIndexInCurrentSecond{};	                        	//当前秒更新累积器
        unsigned long sleepTime{};		                                //休眠时间
        int loops{};	                                            	//跳帧内次数
        void _UpdateFPS(uint32_t & _fps) {
            if (currentTick - lastSecondFrameTick > 1000) {                 //绘制累积达到1s
                lastSecondFrameTick = currentTick;                          //更新上一秒绘制的tick
                _fps = frameIndexInCurrentSecond;                           //更新FPS
                frameIndexInCurrentSecond = 0;                              //清空累积器
            }
        }
        void _UpdateGameSpeed(uint32_t & _gs) {
            if (currentTick - lastSecondGameTick > 1000) {                  //更新累积达到1s
                lastSecondGameTick = currentTick;                           //更新上一秒更新的tick
                _gs = updateIndexInCurrentSecond;                           //更新游戏速率
                updateIndexInCurrentSecond = 0;                             //清空累积器
            }
        }
        void BeginLoopUpdate() {
            loops = 0;
        }
        bool CanLoopUpdate(const unsigned int _MAX_FRAME_SKIP) {
            uint64_t cur = TickRunner::GetCurrentTickCount();
            return cur > nextGameTick && loops < _MAX_FRAME_SKIP;
        }
        void NextLoopUpdate(const unsigned int _SKIP_TICKS) {
            updateIndexInCurrentSecond++;
            nextGameTick += _SKIP_TICKS;
            loops++;
        }
        void EndLoopUpdate() {
            //nextGameTick = TickRunner::GetCurrentTickCount();
        }
        void TimingLoopRender(const unsigned int _SKIP_TICKS, uint32_t & _fps, uint32_t & _gs) {
            frameIndexInCurrentSecond++;

            nextFrameTick += _SKIP_TICKS;
            currentTick = TickRunner::GetCurrentTickCount();

            _UpdateFPS(_fps);
            _UpdateGameSpeed(_gs);
        }
        void CheckSleep(bool _isMaxFps) {
            if (nextFrameTick >= currentTick) {		//休眠指定时间
                if (!_isMaxFps) {
                    sleepTime = (unsigned long) (nextFrameTick - currentTick);
                    TickRunner::DoSleep(sleepTime);
                }
            }
            else {
                //出现了延迟，不进行休眠
            }
        }
    };

    // 主循环源码
    // https://dewitters.com/dewitters-gameloop/
    // 该循环算法优先确保更新逻辑执行次数正常，可牺牲渲染逻辑执行次数
    void Game::_DoMainLoop() {
        const unsigned int FRAMES_PER_SECOND = 60;		                //游戏逻辑每秒处理次数
        const unsigned int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;		//游戏逻辑恒定更新速率
        const unsigned int MAX_FRAME_SKIP = 5;		                    //最大单次跳帧的次数，超过该次数就必须绘制新的图像
        TickTemp tickTemp;
        bool isFirstLoopMsg = false;
        GameWindowMessage gameMessage{};
        while (m_isRunning) {
            if (m_isServer) {
                // 服务端主循环
                _StateTrigger();
                //主逻辑
                tickTemp.BeginLoopUpdate();
                while (tickTemp.CanLoopUpdate(MAX_FRAME_SKIP)) {
                    _MainUpdate();
                    tickTemp.NextLoopUpdate(SKIP_TICKS);
                }
                tickTemp.EndLoopUpdate();
                tickTemp.TimingLoopRender(SKIP_TICKS, m_state.framePreSecond, m_state.gameSpeed);
                tickTemp.CheckSleep(m_state.isMaxFps);
            }
            else {

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
                while (tickTemp.CanLoopUpdate(MAX_FRAME_SKIP)) {

                    //消息（一次主逻辑更新一一对应一次消息更新）
                    if (!isFirstLoopMsg) {
                        _ProcessWindowMessage(gameMessage);
                    }
                    isFirstLoopMsg = false;
                    isCurrentLoopRunUpdate = true;

                    //主逻辑
                    _MainUpdate();

                    tickTemp.NextLoopUpdate(SKIP_TICKS);
                }
                tickTemp.EndLoopUpdate();

                bool isCurrentLoopRender = (!isCurrentLoopChangeUpdater) || (isCurrentLoopChangeUpdater && isCurrentLoopRunUpdate);

                //主绘制
                if (isCurrentLoopRender && _CheckRenderRunning()) {

                    _MainRender();

                    tickTemp.TimingLoopRender(SKIP_TICKS, m_state.framePreSecond, m_state.gameSpeed);
                    tickTemp.CheckSleep(m_state.isMaxFps);
                } else {        //不满足渲染条件（设备丢失），修复设备
                    _FixRender();
                    tickTemp = TickTemp();
                }
            }

            //检测外部调试器注入
            if (_PebIsDebuggedApproach()) {
                // TODO 处理调试器注入
            }
        }
    }

    void Game::_MainRender() {

    }

    void Game::_MainUpdate() {
        static int t=0;
        t++;
        TCE_LOG_INFO("total %d fps %d gs %d", t, m_state.framePreSecond, m_state.gameSpeed);
    }

    bool Game::_StateTrigger() {
        return m_state.CheckState();
    }

    bool Game::_CheckRenderRunning() {
#if defined(_WINDOWS)
        return pDX->GetDeviceState() == D3D_OK &&
               !pDX->IsReset();     //GetForegroundWindow() == hwnd &&
#endif
        return true;        //测试
        return false;
    }

    void Game::_FixRender() {
#if defined(_WINDOWS)
        bool b1 = pDX->GetDeviceState() == D3DERR_DEVICENOTRESET;
        bool b2 = pDX->IsReset();
        if (b1 || b2) {
            pDX->Reset();
        }
#endif
    }

    bool Game::_ProcessWindowMessage(GameWindowMessage & gameMessage) {
#if defined(_WINDOWS)
        if (PeekMessage(&gameMessage.msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&gameMessage.msg);
            DispatchMessage(&gameMessage.msg);
            return true;
        }
#endif
        return false;
    }

    void Game::_CheckWindowFront() {
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
}
