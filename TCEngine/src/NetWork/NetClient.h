#pragma once

#include <cstdint>
#include <mutex>
#include <Utils/ByteStream.h>
#include "TCSocket.h"
#include <array>

namespace Tce {

    class NetPacketReader;

    //临时接收缓存8MB
    const int MAX_RECV_TEMP_BUFFER_SIZE = 1024 * 1024 * 8;
    //最大允许缓存大小1MB
    const int MAX_ALLOW_BUFFER_SIZE = 1024 * 1024;

    class NetClient {
    private:
        TCSocket mSocket;                   //客户端SOCKET
        std::array<uint8_t, MAX_RECV_TEMP_BUFFER_SIZE> mTempBuffer;
        ByteStream mSendBuffer;
        ByteStream mRecvBuffer;
        std::mutex mRecvLock;
        bool mIsRunning{};
    public:
        // 开始连接
        void StartConnection(const char * serverIP, int serverPort);
        // 发送缓存
        void SendAll();
        // 接收缓存
        void RecieveAll(NetPacketReader *pNetPacketReader);
    private:
        void StartRecieveThread();
        // 接收线程
        void _RecieveThreadFunction();
    };

}