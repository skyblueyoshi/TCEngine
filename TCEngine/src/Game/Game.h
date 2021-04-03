#pragma once

namespace Tce {

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
	private:
		bool m_isServer{false};		// 当前游戏环境是否为服务端，否则为客户端
		bool m_isRunning{false};	// 当前游戏环境正在运行
	public:

	};
}