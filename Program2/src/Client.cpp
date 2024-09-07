#include "Client.h"


Client::Client() : clientSocket(-1), ipAddress("127.0.0.1"), port(5555), connectFlag(false)
{}

Client::~Client()
{
    if (clientSocket != -1) {
        close(clientSocket);
    }
}

void Client::init()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("[-] Error creating socket");
        return;
    }

    info.sin_family = AF_INET;
    info.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &info.sin_addr) <= 0) {
        perror("[-] Invalid address");
        close(clientSocket);
        return;
    }

    if (connect(clientSocket, (sockaddr*)&info, sizeof(info)) < 0) {
        perror("[-] Connection failed");
        close(clientSocket);
        return;
    }

    connectFlag = true;
    std::cout << "[+] Connected to server." << std::endl;
}

bool Client::Connection()
{
    init();
    return connectFlag;
}

void Client::ProcessingData()
{
    while (connectFlag) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int recvLength = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (recvLength > 0) {
            std::string message(buffer, recvLength);
            std::cout << "Received: " << message << std::endl;

            if (correctData(message)) {
                std::cout << "Data is correct." << std::endl;
            } else {
                std::cout << "Data is incorrect." << std::endl;
            }
        } else if (recvLength == 0) {
            connectFlag = false;
            std::cout << "[-] Server closed connection." << std::endl;
        } else {
            perror("[-] Receive failed");
            connectFlag = false;
        }
    }

    close(clientSocket);
}

bool Client::correctData(const std::string& message)
{
    if ((message.size() > 2) && (std::stoi(message) % 32 == 0))
        return true;
    return false;
}