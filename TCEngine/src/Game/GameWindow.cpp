#include "GameWindow.h"
#include "../Graphics/Graphics.h"
#include <android_native_app_glue.h>

static void android_handle_cmd(struct android_app* app, int32_t cmd) {
    using namespace Tce;
    auto * pGameWindow = static_cast<GameWindow*>(app->userData);
    assert(pGameWindow);
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            pGameWindow->OnInitWindow();
            break;
        case APP_CMD_DESTROY:
            pGameWindow->OnDestroy();
            break;
        case APP_CMD_TERM_WINDOW:
            pGameWindow->OnTermWindow();
            break;
        case APP_CMD_RESUME:
            pGameWindow->OnResume();
            break;
        case APP_CMD_PAUSE:
            pGameWindow->OnPause();
            break;
        default:
            break;

    }
}

namespace Tce {

    GameWindow::GameWindow(std::shared_ptr<AppState> & pAppState, std::shared_ptr<Graphics> & pGraphics)
        : m_pAppState(pAppState), m_pGraphics(pGraphics) {
        auto pAndroidState = m_pAppState->GetAndroidState();
        pAndroidState->onAppCmd = android_handle_cmd;
        pAndroidState->userData = static_cast<void*>(this);
    }

    void GameWindow::OnInitWindow() {
        if (m_pAppState->GetAndroidState()->window) {
            m_pGraphics->Init(m_pAppState);
        }
    }

    void GameWindow::OnDestroy() {
        m_pGraphics->Destroy();
    }

    void GameWindow::OnTermWindow() {
        m_pGraphics->Destroy();
    }

    void GameWindow::OnResume() {

    }

    void GameWindow::OnPause() {

    }
}