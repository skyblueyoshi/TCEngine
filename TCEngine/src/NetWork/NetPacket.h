#pragma once

#include "TCUtils.h"
#include "TCByteStream.h"

namespace Tce {

    // 一个完整的网络数据包
    class NetPacket {
    public:
        uint32_t _packetId{};
        NetPacket(uint32_t packetId) : _packetId(packetId) {}
        virtual void WriteToStream(ByteStream &bs) = 0;
        virtual void ReadFromStream(ByteStream &bs) = 0;
    };

    class XXXPacket : public NetPacket {
    public:
        int x{};
        int y{};

        XXXPacket() : NetPacket(1) {}

        void WriteToStream(ByteStream &bs) {
            bs.Write(x);
            bs.Write(y);
        }

        void ReadFromStream(ByteStream &bs) {
            bs.Read(x);
            bs.Read(y);
        }
    };

}