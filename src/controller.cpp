#include <iostream>
#include <cstring>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "192.168.0.X" // Replace with the IP address of the Adafruit Metro M0
#define SERVER_PORT 1234        // Replace with the port number used by the Metro M0 UDP server

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Failed to convert IP address." << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    char key;
    while (true) {
        std::cout << "Enter W, A, S, or D to control the outputs (Q to quit): ";
        std::cin >> key;

        if (key == 'Q' || key == 'q') {
            break;
        }

        int output;
        switch (key) {
            case 'W':
            case 'w':
                output = 1;
                break;
            case 'A':
            case 'a':
                output = 2;
                break;
            case 'S':
            case 's':
                output = 3;
                break;
            case 'D':
            case 'd':
                output = 4;
                break;
            default:
                std::cout << "Invalid input." << std::endl;
                continue;
        }

        // Send the output number to the UDP server on the Metro M0
        if (sendto(sock, (const char*)&output, sizeof(output), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
            std::cerr << "Failed to send data." << std::endl;
            closesocket(sock);
            WSACleanup();
            return 1;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
