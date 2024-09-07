#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>


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
    void handleClient(int clientSocket);
    void listening();
    void clientDisconnected(int clientSocket);

private:
    sockaddr_in info;
    int serverSocket;

private:
    int port;
    std::string ipAddress;
    std::mutex mx;

private:
    std::vector<int> clients;
};