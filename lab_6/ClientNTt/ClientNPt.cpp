#include "stdafx.h"///TransactNamedPipe

#define PIPE_NAME L"\\\\.\\pipe\\Tube"

int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "ClientNPt" << endl;

    HANDLE hPipe;
    DWORD ps;
    DWORD state = PIPE_READMODE_MESSAGE;

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

        if (!SetNamedPipeHandleState(hPipe, &state, NULL, NULL)) 
        {
            throw SetErrorMsgText("SetNamedPipeHandleState: ", GetLastError());
        }

        int message_count = 100;
        char obuf[50];
        char ibuf[50];

        const clock_t start = clock();

        for (int i = 1; i <= message_count; i++)
        {
            string obufstr = "Hello from ClientNPt " + to_string(i);
            strcpy_s(obuf, obufstr.c_str());

            if (TransactNamedPipe(hPipe,
                obuf,
                sizeof(obuf),
                ibuf, 
                sizeof(ibuf),
                &ps, 
                NULL))
                cout << ibuf << endl;
            else
                throw SetErrorMsgText("TransactNamedPipe: ", GetLastError());
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