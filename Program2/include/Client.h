#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <thread>

class Client
{
public:
    Client();
    ~Client();

public:
    bool Connection();
    void ProcessingData();

private:
    bool CorrectData();

private:
    bool connectFlag;
    int connectSocket;
    std::string message;
};
