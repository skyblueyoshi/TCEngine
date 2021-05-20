#pragma once

#include "TCUtils.h"

namespace Tce {

    // SOCKET地址
    class TCSocketAddress {
    public:
        short sinFamily;      //协议簇
        String ip;         //IP地址
        uint16_t port;         //端口号
        // 构建一个SOCKET地址
        TCSocketAddress(String _ip, uint16_t _port);
    };

    // SOCKET(TCP)实现
    class TCSocket {
    public:
        const TceSocketHandler kInvalidSocket = (TceSocketHandler)(~0);
    private:
        TceSocketHandler _socket{kInvalidSocket};
        bool _isSingle{false};

    public:
        TCSocket() = default;
        TCSocket(const TCSocket& s) = default;
        TCSocket(TceSocketHandler socket) : _socket(socket) {}

        TCSocket& operator=(const TCSocket& s);

        // 创建一个TCP协议的SOCKET
        // @return SOCKET对象
        static TCSocket CreateTCPSocket();

        // 创建一个模拟SOCKET
        // @return SOCKET对象
        static TCSocket CreateSingleSocket();

        // 关闭SOCKET
        void Close();

        // 设置超时
        // @param sec 超时秒数
        // @param usec 超时微秒数
        void SetTimeOut(long sec = 120, long usec = 0);

        // 连接到指定地址
        // @param address 指定地址
        void Connect(const TCSocketAddress& address);

        // 发送数据
        // @param buffer 缓冲区起点
        // @param size 缓冲区长度
        void Send(const char *buffer, size_t size);

        // 接收数据，返回是否接收数据长度
        // @param buffer 缓冲区起点
        // @param size 缓冲区长度
        // @return 接收数据长度
        size_t Recieve(char *buffer, size_t maxSize);

        // 判断当前SOCKET是否可用
        bool IsEnabled() const;

        // 获取错误码
        // @return 错误码
        static int GetErrorCode();
    };

}