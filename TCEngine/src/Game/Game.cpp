
#include <exception>
#include <Utils/TickRunner.h>
#include "Game.h"
#include "Utils/Log.h"

#define GET_SERVER_CLIENT_NAME(isServer) ((isServer) ? "Server" : "Client")

namespace Tce {

    Tce::Game::Game(bool isServer) : m_isServer(isServer) {

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

    bool Game::_StateTrigger() {
        return m_state.CheckState();
    }

    TickInGame::TickInGame() : currentTick(TickRunner::GetCurrentTickCount()) {

    }

    void TickInGame::BeginLoopUpdate() {
        loops = 0;
    }

    bool TickInGame::CanLoopUpdate() {
        uint64_t cur = TickRunner::GetCurrentTickCount();
        return cur > nextGameTick && loops < MAX_FRAME_SKIP;
    }

    void TickInGame::NextLoopUpdate() {
        updateIndexInCurrentSecond++;
        nextGameTick += SKIP_TICKS;
        loops++;
    }

    void TickInGame::EndLoopUpdate() {
        loops = 0;
        //nextGameTick = TickRunner::GetCurrentTickCount();
    }

    void TickInGame::TimingLoopRender(uint32_t &_fps, uint32_t &_gs) {
        frameIndexInCurrentSecond++;

        nextFrameTick += SKIP_TICKS;
        currentTick = TickRunner::GetCurrentTickCount();

        _UpdateFPS(_fps);
        _UpdateGameSpeed(_gs);
    }

    void TickInGame::CheckSleep(bool _isMaxFps) {
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

    void TickInGame::_UpdateFPS(uint32_t &_fps) {
        if (currentTick - lastSecondFrameTick > 1000) {                 //绘制累积达到1s
            lastSecondFrameTick = currentTick;                          //更新上一秒绘制的tick
            _fps = frameIndexInCurrentSecond;                           //更新FPS
            frameIndexInCurrentSecond = 0;                              //清空累积器
        }
    }

    void TickInGame::_UpdateGameSpeed(uint32_t &_gs) {
        if (currentTick - lastSecondGameTick > 1000) {                  //更新累积达到1s
            lastSecondGameTick = currentTick;                           //更新上一秒更新的tick
            _gs = updateIndexInCurrentSecond;                           //更新游戏速率
            updateIndexInCurrentSecond = 0;                             //清空累积器
        }
    }
}
