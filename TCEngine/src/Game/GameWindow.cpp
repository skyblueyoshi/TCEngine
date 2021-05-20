#include "GameWindow.h"
#ifdef _TC_ANDROID
#include <android_native_app_glue.h>
#endif

#ifdef _TC_ANDROID
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
#endif

namespace Tce {

    GameWindow::GameWindow(std::shared_ptr<AppState> & pAppState, std::shared_ptr<GraphicsDevice> & pGraphicsDevice)
        : m_pAppState(pAppState), m_pGraphicsDevice(pGraphicsDevice) {
#ifdef _TC_ANDROID
        auto pAndroidState = m_pAppState->GetAndroidState();
        pAndroidState->onAppCmd = android_handle_cmd;
        pAndroidState->userData = static_cast<void*>(this);
#endif
    }

    void GameWindow::OnInitWindow() {
#ifdef _TC_ANDROID
        if (m_pAppState->GetAndroidState()->window) {
            m_pGraphicsDevice->Init(m_pAppState.get());
        }
#endif
    }

    void GameWindow::OnDestroy() {
        m_pGraphicsDevice->Destroy();
    }

    void GameWindow::OnTermWindow() {
        m_pGraphicsDevice->Destroy();
    }

    void GameWindow::OnResume() {

    }

    void GameWindow::OnPause() {

    }
}