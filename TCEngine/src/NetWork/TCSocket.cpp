#include "TCSocket.h"

#ifndef _TC_WINDOWS
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <stdexcept>
#include <utility>
#include <fstream>
#include <arpa/inet.h>
#endif

#include "ExceptionHelper.h"

namespace Tce {

    TCSocket& TCSocket::operator=(const TCSocket& s) {
        if (this != &s) {
            _socket = s._socket;
        }
        return *this;
    }

    TCSocket TCSocket::CreateTCPSocket() {
        TCSocket result(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
        if (!result.IsEnabled()) {
            throw std::runtime_error("Cannot create TCP socket.");
        }
        return result;
    }

    TCSocket TCSocket::CreateSingleSocket() {


        return TCSocket();
    }

    bool TCSocket::IsEnabled() const {
        return _socket != kInvalidSocket;
    }

    void TCSocket::SetTimeOut(long sec, long usec) {
        timeval tm{};        //设置超时
        tm.tv_sec = sec;
        tm.tv_usec = usec;
        int iResult = setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char *) &tm, sizeof(tm));
        if (iResult < 0) {
            THROW_RUNTIME_ERROR("Failed to set timeout socket. Error code: %d",
                                GetErrorCode());
        }
    }

    int TCSocket::GetErrorCode() {
#ifdef _WINDOWS
        return WSAGetLastError();
#else
        return errno;
#endif
    }

    void TCSocket::Close() {
        if (IsEnabled()) {
            //TODO CLOSE SOCKET
#ifdef _WINDOWS
            closesocket(_socket);
#else
            close(_socket);
#endif
            _socket = kInvalidSocket;
        }

    }

    void TCSocket::Connect(const TCSocketAddress& address) {
        sockaddr_in serAddr{};
        serAddr.sin_family = address.sinFamily;
        serAddr.sin_port = htons(address.port);

#ifndef _TC_WINDOWS
        if (inet_pton(AF_INET, address.ip.Data(), &serAddr.sin_addr) <= 0) {
            THROW_RUNTIME_ERROR("Failed to call inet_pton from ip \"%s\". Error code: %d",
                                address.ip.Data(),
                                GetErrorCode());
        }
#endif

        if (connect(_socket, (sockaddr *) &serAddr, sizeof(serAddr)) < 0) {
            //连接失败
            THROW_RUNTIME_ERROR("Connect failed. Error code: %d",
                                GetErrorCode());
        }
    }

    void TCSocket::Send(const char *buffer, size_t size) {
        send(_socket, buffer, (int)size, 0);
    }

    size_t TCSocket::Recieve(char *buffer, size_t maxSize) {
        int iResult = 0;
#ifdef _TC_WINDOWS
        iResult = recv(_socket, buffer, (int)maxSize, 0);
#else
        iResult = read(_socket, buffer, maxSize);
#endif
        if (iResult > 0)
            return (size_t)iResult;
        return 0;
    }

    TCSocketAddress::TCSocketAddress(String _ip, u_short _port)
            : sinFamily(AF_INET), ip(std::move(_ip)), port(_port) {

    }
}