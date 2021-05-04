#include "TCSocket.h"
#include <exception>

#ifdef _WINDOWS
#include <Windows.h>
#else

#include <unistd.h>          /* for close() */
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
        return _socket != TC_INVALID_SOCKET;
    }

    void TCSocket::SetTimeOut(long sec, long usec) {
        timeval tm{};        //设置超时
        tm.tv_sec = 100;
        tm.tv_usec = 0;
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
            close(_socket);
            _socket = TC_INVALID_SOCKET;
        }

    }

    void TCSocket::Connect(const TCSocketAddress& address) {
        sockaddr_in serAddr{};
        serAddr.sin_family = address.sinFamily;
        serAddr.sin_port = htons(address.port);

        if (inet_pton(AF_INET, address.ip.c_str(), &serAddr.sin_addr) <= 0) {
            THROW_RUNTIME_ERROR("Failed to call inet_pton from ip \"%s\". Error code: %d",
                                address.ip.c_str(),
                                GetErrorCode());
        }


        if (connect(_socket, (sockaddr *) &serAddr, sizeof(serAddr)) < 0) {
            //连接失败
            THROW_RUNTIME_ERROR("Connect failed. Error code: %d",
                                GetErrorCode());
        }
    }

    void TCSocket::Send(const char *buffer, int size) {
        send(_socket, buffer, size, 0);
    }

    size_t TCSocket::Recieve(char *buffer, int maxSize) {
        int iResult = 0;
#ifdef _WINDOWS
        iResult = recv(_socket, buffer, maxSize, 0);
#else
        iResult = read(_socket, buffer, maxSize);
#endif
        if (iResult > 0)
            return iResult;
        return 0;
    }

    TCSocketAddress::TCSocketAddress(std::string _ip, u_short _port)
            : sinFamily(AF_INET), ip(std::move(_ip)), port(_port) {

    }
}