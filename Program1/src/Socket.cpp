#include "../include/Socket.h"


Socket::Socket() : port(5555), ipAddress("127.0.0.1"), serverSocket(-1), info{ 0 } 
{
    work();
}

Socket::~Socket() 
{
    if (serverSocket != -1) {
        close(serverSocket);
    }
}

void Socket::init() 
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("[-] Error creating socket");
        return;
    }

    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (bind(serverSocket, (sockaddr*)&info, sizeof(info)) < 0) {
        perror("[-] Error bind socket");
        close(serverSocket);
        return;
    }

    std::cout << "[+] The server is running." << std::endl;
}

void Socket::work() 
{
    init();

    std::thread listeningThread(&Socket::listening, this);
    listeningThread.detach();
}

void Socket::listening() 
{
    if (listen(serverSocket, SOMAXCONN) < 0) {
        perror("[-] Error listen");
        close(serverSocket);
        return;
    }

    while (true) {
        sockaddr_in clientInfo;
        socklen_t clientInfoLength = sizeof(clientInfo);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientInfo, &clientInfoLength);

        if (clientSocket < 0) {
            perror("[-] Accept failed");
            continue;
        }

        clients.push_back(clientSocket);
        std::cout << std::endl << "[+] Client connected from: " << inet_ntoa(clientInfo.sin_addr) << ":" << ntohs(clientInfo.sin_port) << std::endl << "Input: ";
        std::thread(&Socket::handleClient, this, clientSocket).detach();
    }
}

void Socket::handleClient(int clientSocket) 
{
    char buffer[512];
    while (true) {
        int recvLength = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (recvLength <= 0) {
            if (recvLength == 0) {
                std::cerr << std::endl << "[-] Client disconnected." << std::endl;
            } else {
                perror("[-] Error receiving data");
            }
            clientDisconnected(clientSocket);
            break;
        }

        std::cout << "Received data: " << std::string(buffer, recvLength) << std::endl;
    }
}

void Socket::sendData(const std::string& data) 
{
    std::lock_guard<std::mutex> lock(mx);

    for (int client : clients) {
        int sendResult = send(client, data.c_str(), data.size(), 0);
        if (sendResult < 0) {
            perror("[-] Failed to send data to client");
        }
    }
}

void Socket::clientDisconnected(int clientSocket) 
{
    std::lock_guard<std::mutex> lock(mx);

    clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
    std::cout << "[+] Client disconnected, socket closed." << std::endl << "Input: ";
    close(clientSocket);
}