#pragma once

#include <memory>
#include "GameState.h"

namespace Tce {

	struct GameWindowMessage {
#if defined(_WINDOWS)
		MSG msg{};
#endif
	};

	// 一个完整的游戏环境
	// 可作为客户端或者服务端
	class Game {
	public:
		Game(bool isServer);
		virtual ~Game() = default;
		// 初始化当前游戏
		// @return 返回是否初始化成功
		bool Init();
		// 运行当前游戏
		void Run();
		// 判断当前游戏环境是否正在运行
		// @return 游戏环境是否运行
		bool IsRunning() const { return m_isRunning; }

	protected:
		// 游戏逻辑更新主函数
		void Update();
		// 游戏渲染主函数，仅客户端调用
		void Render();

	private:
		// 执行主循环
		void _DoMainLoop();
		// 执行主更新
		void _MainUpdate();
		// 执行主渲染
		void _MainRender();
		// 游戏状态变化检测
		// @return 返回游戏状态是否发生变化
		bool _StateTrigger();
		// 在渲染刻中，检测渲染器是否正常
		// @return 返回渲染器是否正常工作
		bool _CheckRenderRunning();
		// 在渲染器异常时修复渲染器
		void _FixRender();
		// 在更新刻中，处理窗口消息
		// @return 消息是否被正常处理
		bool _ProcessWindowMessage(GameWindowMessage & gameMessage);
		// 检测窗口是否置前，保存到state中
		void _CheckWindowFront();
	private:
		bool m_isServer{false};						// 当前游戏环境是否为服务端，否则为客户端
		bool m_isRunning{false};					// 当前游戏环境正在运行
		GameState m_state;							// 当前游戏状态

	};
}