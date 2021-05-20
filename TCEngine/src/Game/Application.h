#pragma once

#include "TCArray.h"
#include "Game.h"
#include "GameWindow.h"

namespace Tce {

	// 应用程序
	class Application {
	public:
		//APP解决方案
		enum EnumSolution {
			SOLUTION_CLIENT,			//仅客户端
			SOLUTION_SERVER,			//仅服务端
			SOLUTION_CLIENT_SERVER		//客户端和服务端均可存在
		};
		Application(std::shared_ptr<AppState> & pAppState, EnumSolution eSolution);
		virtual ~Application() = default;
		// 初始化应用程序
		// @return true表示初始化成功，false表示初始化失败
		bool Init();
		// 运行应用程序
		void Run();
	private:
	    enum EnumGameIndex {
	        GAME_INDEX_CLIENT,
	        GAME_INDEX_SERVER,
	        GAME_INDEX_MAX
	    };
        EnumSolution m_eSolution{SOLUTION_CLIENT};	                        // APP方案
		std::shared_ptr<AppState> m_pAppState;					            // 应用状态
		Array<std::unique_ptr<Game>, GAME_INDEX_MAX> m_pGames;         // 游戏示例表

		std::shared_ptr<GraphicsDevice> m_pGraphicsDevice;					// 主渲染类
		std::unique_ptr<GameWindow> m_pGameWindow;                          // 游戏屏幕类
	};
}