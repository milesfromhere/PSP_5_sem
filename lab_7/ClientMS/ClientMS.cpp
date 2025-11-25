#include "stdafx.h"

#define NAME_SLOT L"\\\\.\\mailslot\\box"

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Mailslot Client..." << endl;

	HANDLE hM;
	DWORD wb;
	char wbuf[300];

	try
	{
		if ((hM = CreateFile(
			NAME_SLOT,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL)) == INVALID_HANDLE_VALUE) 
		{
			throw SetErrorMsgText("Create File Error", WSAGetLastError());
		}

		for (int i = 0; i < 30; i++) 
		{
			string writebufstr = "Hello from Client " + to_string(i + 1);
			strcpy_s(wbuf, writebufstr.c_str());

			if (!WriteFile(hM, wbuf, sizeof(wbuf), &wb, NULL))
				throw SetErrorMsgText("Write File Error", WSAGetLastError());

		}

		strcpy_s(wbuf, "STOP");
		if (!WriteFile(hM, wbuf, sizeof(wbuf), &wb, NULL))
			throw SetErrorMsgText("Write File Error", WSAGetLastError());

		CloseHandle(hM);
	}
	catch (string error)
	{
		cout << error << endl;
	}
}