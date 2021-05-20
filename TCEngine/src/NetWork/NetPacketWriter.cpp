#include "NetPacketWriter.h"
#include "NetSession.h"

namespace Tce {

    void NetPacketWriter::Flush(ByteStream &outputs) {

    }

    void NetPacketWriter::Write(NetSession &netSession, NetPacket *pNetPacket) {
        mTempStream.Clear();
        pNetPacket->WriteToStream(mTempStream);
        auto &sendStream = netSession.mSendStream;
        sendStream.WriteVarInt(pNetPacket->_packetId);
        sendStream.Write(mTempStream);
    }

}

