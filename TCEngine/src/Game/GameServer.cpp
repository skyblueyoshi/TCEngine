
#include "GameServer.h"
#include "Game.h"


namespace Tce {

    GameServer::GameServer() : Game(true) {

    }

    bool GameServer::Init() {
        return true;
    }


    // 主循环源码
    // https://dewitters.com/dewitters-gameloop/
    // 该循环算法优先确保更新逻辑执行次数正常，可牺牲渲染逻辑执行次数
    void GameServer::_DoMainLoop() {
        TickInGame tickTemp;
        while (m_isRunning) {
            // 服务端主循环
            _StateTrigger();
            //主逻辑
            tickTemp.BeginLoopUpdate();
            while (tickTemp.CanLoopUpdate()) {
                _MainUpdate();
                tickTemp.NextLoopUpdate();
            }
            tickTemp.EndLoopUpdate();
            tickTemp.TimingLoopRender(m_state.framePreSecond, m_state.gameSpeed);
            tickTemp.CheckSleep(m_state.isMaxFps);
        }
    }

    void Game::_MainUpdate() {
        Update();
    }

}

