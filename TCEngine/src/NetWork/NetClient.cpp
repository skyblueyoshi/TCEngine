#include <exception>
#include "NetClient.h"
#include "NetPacketReader.h"
#include <thread>

namespace Tce {


    void NetClient::StartConnection(const char *serverIP, int serverPort) {
        try {
            mSocket = TCSocket::CreateTCPSocket();
            mSocket.SetTimeOut(120);
            mSocket.Connect(TCSocketAddress(serverIP, serverPort));
            StartRecieveThread();
        }
        catch (const std::exception &ex) {

        }
    }

    void NetClient::SendAll() {
        if (!mSendBuffer.IsEmpty()) {
            mSocket.Send((char *) mSendBuffer.GetBase(),
                         mSendBuffer.GetLength());
            mSendBuffer.Reset();
        }
    }

    void NetClient::_RecieveThreadFunction() {
        while (mIsRunning) {
            int count = mSocket.Recieve((char *) mTempBuffer.data(),
                                        mTempBuffer.size());
            if (count > 0) {
                std::lock_guard<std::mutex> lockGuard(mRecvLock);
                mRecvBuffer.WriteBatch(mTempBuffer.data(), count);
            }
        }
        mSocket.Close();
    }

    void NetClient::StartRecieveThread() {
        std::thread t1 = std::thread(&NetClient::_RecieveThreadFunction, this);
        t1.detach();
    }

    void NetClient::RecieveAll(NetPacketReader *pNetPacketReader) {
        std::lock_guard<std::mutex> lockGuard(mRecvLock);
        NetPacketReader::EnumResult result = NetPacketReader::RESULT_SUCCESS;
        while (result == NetPacketReader::RESULT_SUCCESS &&
               mRecvBuffer.CanRead()) {
            // TODO 环形缓冲区
            break;
            //result = pNetPacketReader->ReadPacket();
        }
        if (mRecvBuffer.GetLength() > 0 && !mRecvBuffer.CanRead()) {
            mRecvBuffer.SetLength(0);
        }
        if (mRecvBuffer.IsEmpty() &&
            mRecvBuffer.GetCapacity() > MAX_ALLOW_BUFFER_SIZE) {
            mRecvBuffer.FreeMemory();
        }
    }
}