#include "Application.h"

#include <memory>
#include "Game.h"
#include "Graphics.h"
#include "GameClient.h"
#include "GameServer.h"
#include "GameWindow.h"

namespace Tce {

	Application::Application(std::shared_ptr<AppState> & pAppState, Application::EnumSolution eSolution)
	: m_eSolution(eSolution), m_pAppState(pAppState) {

	}

	bool Application::Init() {
		switch (m_eSolution) {
			case SOLUTION_CLIENT:
                m_pGraphics = std::make_shared<Graphics>();
				m_pGames[GAME_INDEX_CLIENT] = std::make_unique<GameClient>(m_pAppState, m_pGraphics);
				m_pGameWindow = std::make_unique<GameWindow>(m_pAppState, m_pGraphics);
				break;
			case SOLUTION_SERVER:
				m_pGames[GAME_INDEX_SERVER] = std::make_unique<GameServer>();
				break;
			default:

				break;
		}
		for (auto &pGame : m_pGames) {
			if (pGame) {
				if (!pGame->Init()){
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
