#include "Application.h"

#include <memory>
#include "Game.h"
#include "GraphicsDevice.h"
#include "GameClient.h"
#include "GameServer.h"
#include "GameWindow.h"
#include "File.h"

namespace Tce {

    Application::Application(std::shared_ptr<AppState> &pAppState,
                             Application::EnumSolution eSolution)
            : m_eSolution(eSolution), m_pAppState(pAppState) {
        File::SetAssetManager(pAppState->GetAndroidState()->activity->assetManager);
    }

    bool Application::Init() {
        switch (m_eSolution) {
            case SOLUTION_CLIENT:
                m_pGraphicsDevice = std::make_shared<GraphicsDevice>();
                m_pGames[GAME_INDEX_CLIENT] = std::make_unique<GameClient>(m_pAppState,
                                                                           m_pGraphicsDevice);
                m_pGameWindow = std::make_unique<GameWindow>(m_pAppState, m_pGraphicsDevice);
                break;
            case SOLUTION_SERVER:
                m_pGames[GAME_INDEX_SERVER] = std::make_unique<GameServer>();
                break;
            default:

                break;
        }
        for (auto &pGame : m_pGames) {
            if (pGame) {
                if (!pGame->Init()) {
                    return false;
                }
            }
        }
        return true;
    }


    void Application::Run() {
        if (m_pGames[GAME_INDEX_CLIENT])
            m_pGames[GAME_INDEX_CLIENT]->Run();
        else if (m_pGames[GAME_INDEX_SERVER])
            m_pGames[GAME_INDEX_SERVER]->Run();
    }

}
