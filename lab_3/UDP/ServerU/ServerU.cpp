#include <iostream>
#include <clocale>
#include <ctime>

#include "ErrorMsgText.h"
#include "Winsock2.h"
using namespace std;

#pragma warning(disable : 4996)
#pragma comment(lib, "WS2_32.lib")  

int main()
{
    setlocale(LC_ALL, "rus");

    WSADATA wsaData;

    SOCKET sS;
    SOCKADDR_IN serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(2000);
    serv.sin_addr.s_addr = INADDR_ANY;

    try
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("WSASturtup: ", WSAGetLastError());
        }

        if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
            throw SetErrorMsgText("socket: ", WSAGetLastError());
        }

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) {
            throw SetErrorMsgText("bind: ", WSAGetLastError());
        }

        SOCKADDR_IN clientInfo;
        memset(&clientInfo, 0, sizeof(clientInfo));
        char ibuf[50];
        int lc = sizeof(clientInfo), lb = 0, lobuf = 0;
        clock_t start, end;
        bool flag = true;

        // Переменные для статистики
        int total_packets = 0;
        int received_packets = 0;
        int lost_packets = 0;
        int session_count = 0;

        while (true)
        {
            // Сброс счетчиков для новой сессии
            total_packets = 0;
            received_packets = 0;
            lost_packets = 0;
            session_count++;

            cout << "\n=== Сессия " << session_count << " ===" << endl;
            start = clock();

            while (true)
            {
                if ((lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clientInfo, &lc)) == SOCKET_ERROR) {
                    throw  SetErrorMsgText("recvfrom: ", WSAGetLastError());
                }

                total_packets++;
                received_packets++;

                if (strcmp(ibuf, "") == 0) {
                    end = clock();
                    double time_elapsed = ((double)(end - start) / CLK_TCK);

                    // Вывод статистики
                    cout << "\n=== СТАТИСТИКА СЕССИИ " << session_count << " ===" << endl;
                    cout << "Время: " << time_elapsed << " с" << endl;
                    cout << "Всего пакетов: " << total_packets << endl;
                    cout << "Принято пакетов: " << received_packets << endl;
                    cout << "Потеряно пакетов: " << lost_packets << endl;
                    cout << "Процент потерь: " << (total_packets > 0 ? (double)lost_packets / total_packets * 100 : 0) << "%" << endl;
                    cout << "Процент доставки: " << (total_packets > 0 ? (double)received_packets / total_packets * 100 : 0) << "%" << endl;
                    cout << "==============================\n" << endl;
                    break;
                }
                cout << "Пакет " << total_packets << ": " << ibuf << endl;
            }
        }
    }
    catch (basic_string<char> error_msg_text) {
        cout << endl << error_msg_text;
    }

    system("pause");
    return 0;
}