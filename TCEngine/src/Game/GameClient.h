#pragma once

#include "Game.h"

namespace Tce {

    class Graphics;
    class AppState;

    class GameClient : public Game {
    public:
        GameClient(std::shared_ptr<AppState> & pAppState, std::shared_ptr<Graphics> & pGraphics);
        bool Init();

    protected:
        // 执行主循环
        void _DoMainLoop();
        // 游戏渲染主函数，仅客户端调用
        void Render();
        // 执行主渲染
        void _MainRender();
        // 在更新刻中，处理窗口消息
        // @return 消息是否被正常处理
        bool _ProcessWindowMessage(GameWindowMessage & gameMessage);
        // 检测窗口是否置前，保存到state中
        void _CheckWindowFront();

    private:
        std::shared_ptr<AppState> m_pAppState;
        std::shared_ptr<Graphics> m_pGraphics;
    };

}