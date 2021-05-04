#pragma once

#include "NetPacket.h"

namespace Tce {

    class NetSession;

    class NetPacketReader {
    private:
        size_t _failTimes{};
        ByteStream mTempStream;
    public:
        const int MAX_WAIT_NEXT_TIMES = 128;        //最多尝试次数
        enum EnumResult {
            RESULT_SUCCESS,     // 读取成功
            RESULT_WAIT_NEXT,   // 等待下一次读取
            RESULT_FAILED       // 读取失败
        };

        EnumResult ReadPacket(NetSession & netSession, NetPacket **ppNetPacket);
    };

}