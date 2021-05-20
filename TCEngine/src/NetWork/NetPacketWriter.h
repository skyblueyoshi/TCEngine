#pragma once

#include "NetPacket.h"

namespace Tce {

    class NetSession;

    class NetPacketWriter {
    private:
        ByteStream mTempStream;
    public:
        NetPacketWriter() = default;
        virtual ~NetPacketWriter() = default;
        void Flush(ByteStream & outputs);

        // 将指定数据包写入到对应会话
        // @param netSession 网络会话
        // @param pNetPacket 数据包
        void Write(NetSession & netSession, NetPacket * pNetPacket);
    };

}