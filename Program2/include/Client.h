#pragma once
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>


class Client
{
public:
    Client();
    ~Client();

public:
    bool Connection();
    void ProcessingData();

private:
    void init();
    bool correctData(const std::string& message);

private:
    sockaddr_in info;
    int clientSocket;

private:
    int port;
    std::string ipAddress;

private:
    bool connectFlag;
};