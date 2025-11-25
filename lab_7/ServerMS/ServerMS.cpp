#include "stdafx.h"

#define NAME_SLOT L"\\\\.\\mailslot\\box"

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Mailslot Server..." << endl;

	HANDLE hM;
	DWORD rb;
	char rbuf[300];

	DWORD waiting_time_1 = MAILSLOT_WAIT_FOREVER;
	DWORD waiting_time_2 = 180000;
	DWORD waiting_time_3 = 5000;

	bool flag = true;
	clock_t start, end;

	try
	{
		if ((hM = CreateMailslot(
			NAME_SLOT,
			300,
			waiting_time_1,
			NULL)) == INVALID_HANDLE_VALUE) 
		{
			throw SetErrorMsgText("Create Mailslot Error", WSAGetLastError());
		}

		while (true) 
		{
			if (ReadFile(hM, rbuf, sizeof(rbuf), &rb, NULL)) 
			{
				cout << rbuf << endl;
				if (flag)
				{
					start = clock();
					flag = false;
				}
			}
			else
				throw "ReadFileError";

			if (strcmp(rbuf, "STOP") == 0) 
			{
				end = clock();
				cout << "Time: " << ((double)(end - start) / CLK_TCK) << "sec" << endl;
				flag = true;
			}
		}

		CloseHandle(hM);
	}
	catch (string error)
	{
		cout << error << endl;
	}
}