#include "Application.h"

#include <memory>
#include "Game.h"

namespace Tce {

	Application::Application(AppState *pAppState, Application::EnumSolution eSolution)
	: m_pAppState(pAppState), m_eSolution(eSolution) {

	}

	bool Application::Init() {
		switch (m_eSolution) {
			case SOLUTION_CLIENT:
				m_pGames[GAME_INDEX_CLIENT] = std::make_unique<Game>(false);
				break;
			case SOLUTION_SERVER:
				m_pGames[GAME_INDEX_SERVER] = std::make_unique<Game>(true);
				break;
			default:

				break;
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
