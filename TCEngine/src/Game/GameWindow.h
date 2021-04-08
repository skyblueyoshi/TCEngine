#pragma once

#include <memory>
#include "AppState.h"
#include "GraphicsDevice.h"

namespace Tce {

    class GameWindow {
    public:
        GameWindow(std::shared_ptr<AppState> & pAppState, std::shared_ptr<GraphicsDevice> & pGraphicsDevice);
        virtual ~GameWindow() = default;
        void OnInitWindow();
        void OnDestroy();
        void OnTermWindow();
        void OnResume();
        void OnPause();

    private:
        std::shared_ptr<AppState> m_pAppState;
        std::shared_ptr<GraphicsDevice> m_pGraphicsDevice;
    };

}
