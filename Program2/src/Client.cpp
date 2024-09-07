#include "../include/Client.h"

Client::Client() : connectSocket(-1), connectFlag(false) {}

Client::~Client()
{
    if (connectSocket != -1) {
        close(connectSocket);
    }
}

bool Client::Connection()
{
    connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == -1) {
        std::cerr << "[-] Error creating socket: " << strerror(errno) << std::endl;
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
    serverAddress.sin_port = htons(5555);

    int connectionResult = connect(connectSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if (connectionResult == -1) {
        std::cerr << "[-] Unable to connect to server: " << strerror(errno) << std::endl;
        close(connectSocket);
        return false;
    }

    std::cout << "[+] Connected to server." << std::endl;
    connectFlag = true;
    return true;
}

void Client::ProcessingData()
{
    while (connectFlag) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int recvLength = recv(connectSocket, buffer, sizeof(buffer), 0);
        if (recvLength > 0) {
            message = buffer;
            std::cout << std::endl << "Received: " << message << std::endl;

            if (CorrectData()) {
                std::cout << "Data is correct." << std::endl;
            }
            else {
                std::cout << "Data is incorrect." << std::endl;
            }
        }
        else if (recvLength == 0) {
            connectFlag = false;
            std::cout << "[-] Server closed connection." << std::endl;
        }
        else {
            connectFlag = false;
            std::cerr << "[-] Receive failed with error: " << strerror(errno) << std::endl;
        }
    }

    close(connectSocket);
}

bool Client::CorrectData()
{
    if ((message.size() > 2) && (std::stoi(message) % 32 == 0))
        return true;
    return false;
}
