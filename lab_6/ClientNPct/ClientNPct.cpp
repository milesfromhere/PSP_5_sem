#include "stdafx.h"///CallNamedPipe 

#define PIPE_NAME L"\\\\.\\pipe\\Tube"

int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "ClientNPct" << endl;

    DWORD ps;

    try
    {
        int message_count = 100;
        char obuf[50] = "Hello from ClientNPct!";
        char ibuf[50];

        const clock_t start = clock();

        for (int i = 1; i <= message_count; i++)
        {
            string obufstr = "Hello from ClientNPt " + to_string(i);
            strcpy_s(obuf, obufstr.c_str());

            if (CallNamedPipe(PIPE_NAME,
                obuf,
                sizeof(obuf),
                ibuf,
                sizeof(ibuf),
                &ps,
                NULL))
                cout << ibuf << endl;
            else
                throw SetErrorMsgText("CallNamedPipe: ", GetLastError());
        }

        const clock_t end = clock();

        cout << "Time: " << (static_cast<double>(end - start) / CLK_TCK) << " c\n";

    }
    catch (string ErrorPipeText)
    {
        cout << endl << ErrorPipeText;
    }

}