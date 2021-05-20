
#include "NetPacketReader.h"
#include "NetSession.h"

namespace Tce {
    NetPacketReader::EnumResult
    NetPacketReader::ReadPacket(NetSession &netSession, NetPacket **ppNetPacket) {
        uint32_t packetId = 0;
        auto &recvStream = netSession.mRecvStream;
        size_t lastPos = recvStream.GetReadPos();
        try {
            recvStream.ReadVarInt(packetId);
            recvStream.Read(mTempStream);
            //TODO 数据包获取
            _failTimes = 0;
            return RESULT_SUCCESS;
        }
        catch (...) {
            recvStream.SetReadPos(lastPos);
            mTempStream.Clear();
            _failTimes++;
            if (_failTimes > MAX_WAIT_NEXT_TIMES) {
                _failTimes = 0;
                return RESULT_FAILED;
            }
            return RESULT_WAIT_NEXT;
        }

    }
}

