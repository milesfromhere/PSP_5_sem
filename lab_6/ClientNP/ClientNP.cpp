#include "stdafx.h" ///create/read/write

#define PIPE_NAME L"\\\\.\\pipe\\Tube"

int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "ClientNP" << endl;

    HANDLE hPipe;
    DWORD ps;

    try
    {
        if ((hPipe = CreateFile(
            PIPE_NAME,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            NULL,
            NULL)) == INVALID_HANDLE_VALUE)
            throw SetErrorMsgText("createfile:", GetLastError());

        int message_count = 100;
        char obuf[50];

        const clock_t start = clock();

        for (int i = 1; i <= message_count; i++)
        {
            string buf = "Hello from ClientNP " + to_string(i);
            if (!WriteFile(hPipe, buf.c_str(), sizeof(buf), &ps, NULL))
                throw SetErrorMsgText("WriteFile: ", GetLastError());

            if (ReadFile(hPipe, obuf, sizeof(obuf), &ps, NULL))
                cout << obuf << endl;
            else
                throw SetErrorMsgText("ReadFile: ", GetLastError());
        }

        const clock_t end = clock();

        cout << "Time: " << (static_cast<double>(end - start) / CLK_TCK) << " c\n";

        CloseHandle(hPipe);
    }
    catch (string ErrorPipeText)
    {
        cout << endl << ErrorPipeText;
    }

}