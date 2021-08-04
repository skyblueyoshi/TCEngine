#pragma once

#include "TCUtils.h"
#include "GameState.h"

namespace Tce {

	class TickInGame {
	public:
		TickInGame();
		void BeginLoopUpdate();
		bool CanLoopUpdate();
		void NextLoopUpdate();
		void EndLoopUpdate();
		void TimingLoopRender(uint32_t & _fps, uint32_t & _gs);
		void CheckSleep(bool _isMaxFps);

	private:
		void _UpdateFPS(uint32_t & _fps);
		void _UpdateGameSpeed(uint32_t & _gs);

		static const unsigned int FRAMES_PER_SECOND = 60;		                //游戏逻辑每秒处理次数
		static const unsigned int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;		//游戏逻辑恒定更新速率
		static const unsigned int MAX_FRAME_SKIP = 5;		                    //最大单次跳帧的次数，超过该次数就必须绘制新的图像
		uint64_t currentTick;													//当前帧计时器
		uint64_t nextGameTick{currentTick};		                       			//下一次游戏更新计时器
		uint64_t nextFrameTick{currentTick};		                    		//下一次帧绘制计时器
		uint64_t lastSecondGameTick{currentTick};		                		//上一秒游戏更新计时器
		uint64_t lastSecondFrameTick{currentTick};		                		//上一帧绘制计时器
		uint32_t frameIndexInCurrentSecond{};	                        			//当前秒绘制累积器
		uint32_t updateIndexInCurrentSecond{};	                        			//当前秒更新累积器
		unsigned long sleepTime{};		                                		//休眠时间
		int loops{};	                                            			//跳帧内次数
	};

	struct GameWindowMessage {
#ifdef _TC_WINDOWS
		MSG msg{};
#endif
	};

	// 一个完整的游戏环境
	// 可作为客户端或者服务端
	class Game {
	public:
		Game(bool isServer = true);
		virtual ~Game() = default;
		// 初始化当前游戏
		// @return 返回是否初始化成功
		virtual bool Init() = 0;
		// 运行当前游戏
		void Run();
		// 判断当前游戏环境是否正在运行
		// @return 游戏环境是否运行
		bool IsRunning() const { return m_isRunning; }

	protected:
		// 执行主循环
		virtual void _DoMainLoop() = 0;
		// 游戏逻辑更新主函数
		void Update() {}
		// 执行主更新
		virtual void _MainUpdate();
		// 游戏状态变化检测
		// @return 返回游戏状态是否发生变化
		bool _StateTrigger();

    protected:
		bool m_isServer{false};						// 当前游戏环境是否为服务端，否则为客户端
		bool m_isRunning{false};					// 当前游戏环境正在运行
		GameState m_state;							// 当前游戏状态

	};
}