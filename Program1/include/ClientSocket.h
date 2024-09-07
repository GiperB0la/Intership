#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>


class ClientSocket
{
public:
    ClientSocket(int clientSocket, sockaddr_in clientInfo, int clientInfoLength)
        : clientSocket(clientSocket), clientInfo(clientInfo), clientInfoLength(clientInfoLength), recvLength(0) {};
    ~ClientSocket() = default;

public:
    int clientSocket;
    sockaddr_in clientInfo;
    std::string message;
    int clientInfoLength;
    int recvLength;
};
