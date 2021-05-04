#pragma once

#include <string>

namespace Tce {

#define TC_INVALID_SOCKET (int)(~0)
#define TC_SOCKET_ERROR (-1)

    // SOCKET地址
    class TCSocketAddress {
    public:
        short sinFamily;      //协议簇
        std::string ip;         //IP地址
        u_short port;         //端口号
        // 构建一个SOCKET地址
        TCSocketAddress(std::string _ip, u_short _port);
    };

    // SOCKET(TCP)实现
    class TCSocket {
    private:
        int _socket{TC_INVALID_SOCKET};
        bool _isSingle{false};

        TCSocket(int socket) : _socket(socket) {}

    public:
        TCSocket() = default;

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
        void Send(const char *buffer, int size);

        // 接收数据，返回是否接收数据长度
        // @param buffer 缓冲区起点
        // @param size 缓冲区长度
        // @return 接收数据长度
        size_t Recieve(char *buffer, int maxSize);

        // 判断当前SOCKET是否可用
        bool IsEnabled() const;

        // 获取错误码
        // @return 错误码
        static int GetErrorCode();
    };

}