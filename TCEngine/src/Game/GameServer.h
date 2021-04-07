#pragma once

#include "Game.h"

namespace Tce {

    class GameServer : public Game {
    public:
        GameServer();
        bool Init();

    protected:
        // 执行主循环
        void _DoMainLoop();
    };

}