#pragma once

#include <cstdint>

namespace Tce {

    // 游戏状态
    class GameState {
    public:
        enum EnumState {
            STATE_LOADING,
            STATE_RUNNING,
            STATE_EXITING
        };
        EnumState state{STATE_RUNNING};         // 游戏状态
        uint32_t gameSpeed{};						// 游戏速率，每秒游戏主更新函数调用次数
        uint32_t framePreSecond{};				    // 帧每秒，每秒游戏渲染函数调用次数
        bool isMaxFps{};                        // 是否启用最大帧
        bool isFrontWindow{};                   // 是否在最前窗口运行
        // 检查状态是否发生变更
        // @return 状态是否变化
        bool CheckState();
    private:
        EnumState m_readyState{};               // 上一主循环的游戏状态
    };

}