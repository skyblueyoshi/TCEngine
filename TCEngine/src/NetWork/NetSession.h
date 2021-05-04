#pragma once

#include "ByteStream.h"

namespace Tce {

    class NetSession {
        friend class NetPacketWriter;
        friend class NetPacketReader;
    private:
        ByteStream mSendStream;
        ByteStream mRecvStream;

    };

}