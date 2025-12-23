#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char** argv)
{
    if (argc < 3) { std::cout << "Usage: Client <server_ip> <port>\n"; return 1; }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    WSADATA wsa{};
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) return 1;

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serv.sin_addr);

    if (connect(s, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR)
    {
        std::cerr << "Connect failed: " << WSAGetLastError() << "\n";
        closesocket(s);
        WSACleanup();
        return 1;
    }
    std::cout << "Connected to " << ip << ":" << port << "\n";
    std::string msg;
    while (true)
    {
        std::getline(std::cin, msg);
        if (msg == "exit") break;
        send(s, msg.c_str(), (int)msg.size(), 0);
        char buf[512];
        int rc = recv(s, buf, sizeof(buf)-1, 0);
        if (rc <= 0) break;
        buf[rc] = '\0';
        std::cout << "Echo: " << buf << std::endl;
    }
    closesocket(s);
    WSACleanup();
    return 0;
}
