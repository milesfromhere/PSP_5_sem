#include "stdafx.h"
#include "Errors.h"

string  GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR:               msgText = "WSAEINTR";				 break;
	case WSAEACCES:              msgText = "WSAEACCES";				 break;						    
	case WSAEFAULT:              msgText = "WSAEFAULT";				 break;
	case WSAEINVAL:              msgText = "WSAEINVAL";				 break;
	case WSAEMFILE:              msgText = "WSAEMFILE";              break;
	case WSAEWOULDBLOCK:         msgText = "WSAEWOULDBLOCK";         break;
	case WSAEINPROGRESS:         msgText = "WSAEINPROGRESS";         break;
	case WSAEALREADY:            msgText = "WSAEALREADY";            break;
	case WSAENOTSOCK:            msgText = "WSAENOTSOCK";            break;
	case WSAEDESTADDRREQ:        msgText = "WSAEDESTADDRREQ";        break;
	case WSAEMSGSIZE:            msgText = "WSAEMSGSIZE";            break;
	case WSAEPROTOTYPE:          msgText = "WSAEPROTOTYPE";          break;
	case WSAENOPROTOOPT:         msgText = "WSAENOPROTOOPT";         break;
	case WSAEPROTONOSUPPORT:     msgText = "WSAEPROTONOSUPPORT";     break;
	case WSAESOCKTNOSUPPORT:     msgText = "WSAESOCKTNOSUPPORT";     break;
	case WSAEOPNOTSUPP:          msgText = "WSAEOPNOTSUPP";          break;
	case WSAEPFNOSUPPORT:        msgText = "WSAEPFNOSUPPORT";        break;
	case WSAEAFNOSUPPORT:        msgText = "WSAEAFNOSUPPORT";        break;
	case WSAEADDRINUSE:          msgText = "WSAEADDRINUSE";          break;
	case WSAEADDRNOTAVAIL:       msgText = "WSAEADDRNOTAVAIL";       break;
	case WSAENETDOWN:            msgText = "WSAENETDOWN";            break;
	case WSAENETUNREACH:         msgText = "WSAENETUNREACH";         break;
	case WSAENETRESET:           msgText = "WSAENETRESET";           break;
	case WSAECONNABORTED:        msgText = "WSAECONNABORTED";        break;
	case WSAECONNRESET:          msgText = "WSAECONNRESET";          break;
	case WSAENOBUFS:             msgText = "WSAENOBUFS";             break;
	case WSAEISCONN:             msgText = "WSAEISCONN";             break;
	case WSAENOTCONN:            msgText = "WSAENOTCONN";            break;
	case WSAESHUTDOWN:           msgText = "WSAESHUTDOWN";           break;
	case WSAETIMEDOUT:           msgText = "WSAETIMEDOUT";           break;
	case WSAECONNREFUSED:        msgText = "WSAECONNREFUSED";        break;
	case WSAEHOSTDOWN:           msgText = "WSAEHOSTDOWN";           break;
	case WSAEHOSTUNREACH:        msgText = "WSAEHOSTUNREACH";        break;
	case WSAEPROCLIM:            msgText = "WSAEPROCLIM";            break;
	case WSASYSNOTREADY:         msgText = "WSASYSNOTREADY";         break;
	case WSAVERNOTSUPPORTED:     msgText = "WSAVERNOTSUPPORTED";     break;
	case WSANOTINITIALISED:      msgText = "WSANOTINITIALISED";      break;
	case WSAEDISCON:             msgText = "WSAEDISCON";             break;
	case WSATYPE_NOT_FOUND:      msgText = "WSATYPE_NOT_FOUND";      break;
	case WSAHOST_NOT_FOUND:      msgText = "WSAHOST_NOT_FOUND";      break;
	case WSATRY_AGAIN:           msgText = "WSATRY_AGAIN";           break;
	case WSANO_RECOVERY:         msgText = "WSANO_RECOVERY";         break;
	case WSANO_DATA:             msgText = "WSANO_DATA";             break;
	case WSA_INVALID_HANDLE:     msgText = "WSA_INVALID_HANDLE";     break;
	case WSA_INVALID_PARAMETER:  msgText = "WSA_INVALID_PARAMETER";  break;
	case WSA_IO_INCOMPLETE:      msgText = "WSA_IO_INCOMPLETE";      break;
	case WSA_IO_PENDING:         msgText = "WSA_IO_PENDING";         break;
	case WSA_NOT_ENOUGH_MEMORY:  msgText = "WSA_NOT_ENOUGH_MEMORY";  break;
	case WSA_OPERATION_ABORTED:  msgText = "WSA_OPERATION_ABORTED";  break;
	case WSAEINVALIDPROCTABLE:   msgText = "WSAEINVALIDPROCTABLE";   break;
	case WSAEINVALIDPROVIDER:    msgText = "WSAEINVALIDPROVIDER";    break;
	case WSAEPROVIDERFAILEDINIT: msgText = "WSAEPROVIDERFAILEDINIT"; break;

	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
	default:                msgText = "***ERROR***";      break;
	};
	return msgText;
};

string  SetErrorMsgText(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};

string  SetPipeError(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};






//#include "stdafx.h"
//
//string GetErrorMsgText(int code) // cформировать текст ошибки
//{
//	string msgText;
//	switch (code)
//	{
//	case WSAEINTR: msgText = "Работа функции прервана"; break;
//	case WSAEACCES:	msgText = "Разрешение отвергнуто"; break;
//	case WSAEFAULT: msgText = "Ошибочный адрес"; break;
//	case WSAEINVAL:	msgText = "Ошибка в аргументе";	break;
//	case WSAEMFILE:	msgText = "Открыто слишком много файлов"; break;
//	case WSAEWOULDBLOCK: msgText = "Ресурс временно недоступен"; break;
//	case WSAEINPROGRESS: msgText = "Операция в процессе развития"; break;
//	case WSAEALREADY: msgText = "Операция уже выполняется";	break;
//	case WSAENOTSOCK: msgText = "Сокет задан неправильно"; break;
//	case WSAEDESTADDRREQ: msgText = "Требуется адрес расположения"; break;
//	case WSAEMSGSIZE: msgText = "Сообщение слишком длинное"; break;
//	case WSAEPROTOTYPE: msgText = "Неправильный тип протокола для сокета"; break;
//	case WSAENOPROTOOPT: msgText = "Ошибка в опции протокола"; break;
//	case WSAEPROTONOSUPPORT: msgText = "Протокол не поддерживается"; break;
//	case WSAESOCKTNOSUPPORT: msgText = "Тип сокета не поддерживается"; break;
//	case WSAEOPNOTSUPP: msgText = "Операция не поддерживается"; break;
//	case WSAEPFNOSUPPORT: msgText = "Тип протоколов не поддерживается"; break;
//	case WSAEAFNOSUPPORT: msgText = "Тип адресов не поддерживается протоколом"; break;
//	case WSAEADDRINUSE: msgText = "Адрес уже используется"; break;
//	case WSAEADDRNOTAVAIL: msgText = "Запрошенный адрес не может быть использован"; break;
//	case WSAENETDOWN: msgText = "Сеть отключена"; break;
//	case WSAENETUNREACH: msgText = "Сеть не достижима"; break;
//	case WSAENETRESET: msgText = "Сеть разорвала соединение"; break;
//	case WSAECONNABORTED: msgText = "Программный отказ связи"; break;
//	case WSAECONNRESET: msgText = "Связь не восстановлена"; break;
//	case WSAENOBUFS: msgText = "Не хватает памяти для буферов"; break;
//	case WSAEISCONN: msgText = "Сокет уже подключен"; break;
//	case WSAENOTCONN: msgText = "Сокет не подключен"; break;
//	case WSAESHUTDOWN: msgText = "Нельзя выполнить send: сокет завершил работу"; break;
//	case WSAETIMEDOUT: msgText = "Закончился отведенный интервал времени"; break;
//	case WSAECONNREFUSED: msgText = "Соединение отклонено"; break;
//	case WSAEHOSTDOWN: msgText = "Хост в неработоспособном состоянии"; break;
//	case WSAEHOSTUNREACH: msgText = "Нет маршрута для хоста"; break;
//	case WSAEPROCLIM: msgText = "Слишком много процессов"; break;
//	case WSASYSNOTREADY: msgText = "Сеть не доступна"; break;
//	case WSAVERNOTSUPPORTED: msgText = "Данная версия недоступна"; break;
//	case WSANOTINITIALISED: msgText = "Не выполнена инициализация WS2_32.dll"; break;
//	case WSAEDISCON: msgText = "Выполняется отключение"; break;
//	case WSATYPE_NOT_FOUND: msgText = "Класс не найден"; break;
//	case WSAHOST_NOT_FOUND: msgText = "Хост не найден"; break;
//	case WSATRY_AGAIN: msgText = "Неавторизованный хост не найден"; break;
//	case WSANO_RECOVERY: msgText = "Неопределенная ошибка"; break;
//	case WSANO_DATA: msgText = "Нет записи запрошенного типа"; break;
//	case WSA_INVALID_HANDLE: msgText = "Указанный дескриптор события с ошибкой"; break;
//	case WSA_INVALID_PARAMETER: msgText = "Один или более параметров с ошибкой"; break;
//	case WSA_IO_INCOMPLETE: msgText = "Объект ввода-вывода не в сигнальном состоянии"; break;
//	case WSA_IO_PENDING: msgText = "Операция завершится позже"; break;
//	case WSA_NOT_ENOUGH_MEMORY: msgText = "Не достаточно памяти"; break;
//	case WSA_OPERATION_ABORTED: msgText = "Операция отвергнута"; break;
//	case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова"; break;
//	default: break;
//	}
//	return msgText;
//};
//
//string SetErrorMsgText(string msgText, int code)
//{
//	return msgText + GetErrorMsgText(code);
//};