#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <atomic>

#pragma comment(lib, "Ws2_32.lib")

std::map<int, SOCKET> listenSockets;
std::atomic<bool> running(true);

void worker_thread(SOCKET s)
{
    char buf[256];
    int rc;
    while ((rc = recv(s, buf, sizeof(buf)-1, 0)) > 0)
    {
        buf[rc] = '\0';
        std::cout << "Client msg: " << buf << std::endl;
        send(s, buf, rc, 0);
    }
    closesocket(s);
    std::cout << "Client disconnected\n";
}

void accept_loop()
{
    while (running)
    {
        for (auto &p : listenSockets)
        {
            SOCKET ls = p.second;
            sockaddr_in cli;
            int l = sizeof(cli);
            SOCKET s = accept(ls, (sockaddr*)&cli, &l);
            if (s != INVALID_SOCKET)
            {
                std::cout << "Accepted connection on port " << p.first << " from " << inet_ntoa(cli.sin_addr) << ":" << ntohs(cli.sin_port) << std::endl;
                std::thread(worker_thread, s).detach();
            }
            else
            {
                int err = WSAGetLastError();
                if (err != WSAEWOULDBLOCK && err != WSAEINTR)
                    std::cerr << "accept error on port " << p.first << " code=" << err << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool open_listen(int port)
{
    if (listenSockets.count(port)) return false;
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) return false;
    u_long nonblk = 1;
    ioctlsocket(s, FIONBIO, &nonblk);
    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    if (bind(s, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR)
    {
        closesocket(s);
        return false;
    }
    if (listen(s, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(s);
        return false;
    }
    listenSockets[port] = s;
    std::cout << "Listening on port " << port << std::endl;
    return true;
}

bool close_listen(int port)
{
    auto it = listenSockets.find(port);
    if (it == listenSockets.end()) return false;
    closesocket(it->second);
    listenSockets.erase(it);
    std::cout << "Closed listen on port " << port << std::endl;
    return true;
}

int main()
{
    WSADATA wsa{};
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) return 1;

    // open default port 2000
    open_listen(2000);

    std::thread acc(accept_loop);

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.size() == 0) continue;
        if (line == "exit") break;
        if (line.rfind("OPEN_ACCEPT ", 0) == 0)
        {
            int port = stoi(line.substr(12));
            if (!open_listen(port)) std::cerr << "Failed to open port " << port << std::endl;
        }
        else if (line.rfind("CLOSE_ACCEPT ", 0) == 0)
        {
            int port = stoi(line.substr(13));
            if (!close_listen(port)) std::cerr << "Failed to close port " << port << std::endl;
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }

    running = false;
    acc.join();
    for (auto &p : listenSockets) closesocket(p.second);
    WSACleanup();
    return 0;
}
