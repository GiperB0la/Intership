#include "../include/Socket.h"


Socket::Socket() : port(5555), ipAddress("127.0.0.1"),
serverSocket(-1), info{ 0 }, infoLength(sizeof(info)) 
{
    work();
}

Socket::~Socket()
{
    close(serverSocket);
}

void Socket::init()
{
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << std::endl << "[-] Error creating socket: " << errno << std::endl;
        return;
    }

    int bindResult = bind(serverSocket, (sockaddr*)&info, infoLength);
    if (bindResult < 0) {
        std::cout << std::endl << "[-] Error bind socket: " << errno << std::endl;
        return;
    }
}

void Socket::work()
{
    init();
    std::thread connectingThread(&Socket::connecting, this);
    connectingThread.detach();
}

void Socket::connecting()
{
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cout << std::endl << "[-] Error listen: " << errno << std::endl;
        close(serverSocket);
        return;
    }

    while (true) {
        sockaddr_in clientInfo;
        socklen_t clientInfoLength = sizeof(clientInfo);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientInfo, &clientInfoLength);
        if (clientSocket < 0) {
            std::cout << "[-] Accept failed: " << errno << std::endl;
            continue;
        }
        ClientSocket client(clientSocket, clientInfo, clientInfoLength);
        std::cout << "[+] Client connected from: " << inet_ntoa(client.clientInfo.sin_addr) << ":" << ntohs(client.clientInfo.sin_port) << std::endl << "Input: ";

        clients.push_back(client);
        std::thread(&Socket::handleClient, this, client).detach();
    }
}

void Socket::handleClient(ClientSocket client)
{
    char buffer[512];
    while (true) {
        int recvLength = recv(client.clientSocket, buffer, sizeof(buffer), 0);
        if (recvLength == 0) {
            std::cout << "[-] Client disconnected." << std::endl;
            close(client.clientSocket);
            clientDisconnected(client);
            break;
        }
        else if (recvLength < 0) {
            std::cout << "[-] Error receiving data: " << errno << std::endl;
            close(client.clientSocket);
            clientDisconnected(client);
            break;
        }
    }

    std::lock_guard<std::mutex> lock(clientMutex);
    clientDisconnected(client);
}

void Socket::clientDisconnected(ClientSocket client)
{
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].clientSocket == client.clientSocket) {
            std::cout << "Client " << i + 1 << " {" << inet_ntoa(client.clientInfo.sin_addr) << ":" << ntohs(client.clientInfo.sin_port) << "} disconnected." << std::endl << "Input: ";
            clients.erase(clients.begin() + i);
        }
    }
}

void Socket::sendData(const std::string& data)
{
    std::lock_guard<std::mutex> lock(clientMutex);
    for (ClientSocket client : clients) {
        int sendResult = send(client.clientSocket, data.c_str(), data.size(), 0);
        if (sendResult < 0) {
            std::cout << "[-] Failed to send data to client: " << errno << std::endl;
        }
    }
}
