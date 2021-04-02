#pragma once

namespace Tce {

	// 一个完整的游戏环境
	// 可作为客户端或者服务端
	class Game {
	public:
		Game(bool isServer);
		virtual ~Game();
		// 初始化当前游戏
		// @return 返回是否初始化成功
		bool Init();
		//运行当前游戏
		void Run();
	private:
		bool m_isServer{false};		//当前游戏环境是否为服务端，否则为客户端
	};
}