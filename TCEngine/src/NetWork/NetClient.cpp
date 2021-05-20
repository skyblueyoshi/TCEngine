#include <thread>
#include "NetClient.h"
#include "NetPacketReader.h"
#include "TCLog.h"

namespace Tce {


    bool NetClient::StartConnection(const char *serverIP, uint16_t serverPort) {
        try {
            mSocket = TCSocket::CreateTCPSocket();
            mSocket.SetTimeOut(120);
            mSocket.Connect(TCSocketAddress(serverIP, serverPort));
            StartRecieveThread();
            return true;
        }
        catch (const std::exception &ex) {
            Log::Error(ex.what());
            return false;
        }
    }

    void NetClient::SendAll() {
        if (!mSendBuffer.Empty()) {
            mSocket.Send((char *) mSendBuffer.Data(),
                         mSendBuffer.Count());
            mSendBuffer.Clear();
        }
    }

    void NetClient::_RecieveThreadFunction() {
        while (mIsRunning) {
            size_t count = mSocket.Recieve((char *) mTempBuffer.Data(),
                                        mTempBuffer.Count());
            if (count > 0) {
                std::lock_guard<std::mutex> lockGuard(mRecvLock);
                mRecvBuffer.WriteBatch(mTempBuffer.Data(), count);
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
        if (mRecvBuffer.Count() > 0 && !mRecvBuffer.CanRead()) {
            mRecvBuffer.SetCount(0);
        }
        if (mRecvBuffer.Empty() &&
            mRecvBuffer.Capacity() > MAX_ALLOW_BUFFER_SIZE) {
            mRecvBuffer.FreeMemory();
        }
    }
}