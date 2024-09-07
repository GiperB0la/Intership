#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "ClientSocket.h"


class Socket
{
public:
    Socket();
    ~Socket();

public:
    void sendData(const std::string& data);

private:
    void work();
    void init();
    void handleClient(ClientSocket client);
    void connecting();
    void clientDisconnected(ClientSocket client);

private:
    int serverSocket;
    std::string ipAddress;
    std::string message;
    int port;
    sockaddr_in info;
    int infoLength;
    std::mutex clientMutex;
    std::vector<ClientSocket> clients;
};
