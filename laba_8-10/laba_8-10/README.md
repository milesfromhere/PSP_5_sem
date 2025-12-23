# Инструкция для защиты лабораторной работы

Короткая цель: собрать и показать работу сервера, консоли и клиентов по сценарию из `task.txt`, продемонстрировать поиск сервера (broadcast/DNS), команды консоли и разобрать ключевые места в коде.

**Сборка**
- Откройте решение `laba_8-10.sln` в Visual Studio.
- Выберите конфигурацию `Debug` и платформу `x64`.
- Build Solution (F7).

Если возникнут ошибки — проверьте precompiled headers (`pch/stdafx`) в проектах и include-пути.

**Быстрый запуск (пример)**
- В Developer Command Prompt или PowerShell перейдите в папку с собранным exe: `ConcurrentServer\\x64\\Debug`.
- Запуск сервера (порт по умолчанию 2000):

```powershell
.\\ConcurrentServer.exe 2000 ServiceLibrary.dll Tube
```

- В другом окне запустите консоль администратора:

```powershell
.\\RConsole.exe
```

- В 4 других окнах/машинах запустите клиентов:

```powershell
.\\ClientT.exe
```

Примечание: `ClientT` по умолчанию использует IP, заданный в исходнике — см. `ClientT/ClientT.cpp` (строки с определением `IP_SERVER`). Если сервер на другой машине, замените `IP_SERVER` на IP сервера или измените код для поиска через broadcast.

**Установка таймера сервисов = 3 минуты**
- В файле [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L14) измените значение переменной `timeOutDisconnect` на 180 (секунд):

```cpp
int timeOutDisconnect = 180; // 3 минуты
```

и пересоберите решение.

**Пошаговый сценарий демонстрации (точные шаги и тайминги)**
1. Запустить сервер: `ConcurrentServer.exe 2000 ServiceLibrary.dll Tube`. Подождать 3–5 секунд.
2. Запустить `RConsole.exe` (консоль администратора). В консоли появится меню команд.
3. На четырёх машинах/окнах запустить `ClientT.exe`. Каждый клиент должен сыграть подключение и показать меню запросов.
4. Подождать 3 минуты (таймер сервисов). Показать в окне сервера, что таймеры вызвали `TimeOUT` (логи). — (демонстрация автоматического отключения).
5. В `RConsole` выбрать `2 - stop` (или отправить `stop`). После этого запустить 5-го клиента: он должен «зависнуть» (не подключиться).
6. В `RConsole` выбрать `1 - start`. 5-й клиент должен успешно подключиться.
7. В `RConsole` выбрать `4 - statistic`. Показать вывод: общее количество подключений, активные, завершившиеся по таймауту и т.д.
8. В `RConsole` выбрать `3 - wait`. Запустить 5-го клиента — он должен ждать свободного слота; после завершения одного из первых 4 клиентов 5-й подключится.
9. В `RConsole` выбрать `6 - shutdown`. Консоль перестаёт принимать команды. Завершите аварийно 2 клиентов (закрыть окно или завершить процесс), оставшиеся отработают до таймаута. После окончания всех клиентов сервер завершится корректно.
10. Снова запустить 4 клиента и выполнить `5 - exit` в консоли: консоль станет недоступна, клиенты должны завершиться с кодом ошибки и сервер корректно завершит работу.

Тайминги: обязательно дать серверу 3 минуты на таймаут сервиса; между крупными шагами оставляйте 3–10 секунд для логов и проверки.

**Что показывать в разборе кода (список файлов и ключевых мест)**
- `ConcurrentServer/ConcurrentServer.cpp`:
  - обработка accept / цикл приёма: [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L109) (функция `AcceptCycle`).
  - установка таймера таймаута для сессии: [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L132-L135) и [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L458-L461) (создание/установка `CreateWaitableTimer`/`SetWaitableTimer`).
  - неблокирующий режим сокета: [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L161-L162) (`ioctlsocket` + FIONBIO).
  - UDP discovery / обработка broadcast: [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L482) (определение `GetRequestFromClient`) и вызов в [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L537).
  - динамическая загрузка библиотек и получение функции `SSS`: [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L318-L319) и [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L583-L584).
  - инициализация критической секции: [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L588).

- `ServiceLibrary/ServiceLibrary.cpp`:
  - таблица сервисов и экспорт `SSS`: [ServiceLibrary/ServiceLibrary.cpp](ServiceLibrary/ServiceLibrary.cpp#L1-L12).
  - реализация сервисов (см. `PrototypeService.h` для деталей работы сокета и `ioctlsocket`): [ServiceLibrary/PrototypeService.h](ServiceLibrary/PrototypeService.h#L98-L99).

- `ClientT/ClientT.cpp`:
  - где задать IP сервера (или включить broadcast): [ClientT/ClientT.cpp](ClientT/ClientT.cpp#L3-L4) и место установки `serv.sin_addr` [ClientT/ClientT.cpp](ClientT/ClientT.cpp#L44).

- `RConsole/RConsole.cpp`:
  - отправка команд через named pipe (меню): [RConsole/RConsole.cpp](RConsole/RConsole.cpp#L1-L40).

Покажите эти места на защите — объясните: почему нужен `CriticalSection`, как работает неблокирующий `accept`, как настроен таймер сессии, как загружаются DLL с сервисами и как через named pipe проходит управление.

**Изменения/подготовка перед демонстрацией**
- Установите `timeOutDisconnect = 180` в [ConcurrentServer/ConcurrentServer.cpp](ConcurrentServer/ConcurrentServer.cpp#L14) и пересоберите.
- В `ClientT/ClientT.cpp` замените `IP_SERVER` на IP-адрес сервера или измените код, чтобы сначала посылать UDP-broadcast `"Hello"` и ждать ответа (ConcurrentServer обрабатывает UDP-запросы — смотрите `GetRequestFromClient`).
- Откройте в `C:\\Windows\\System32\\drivers\\etc\\hosts` запись вида:

```
192.168.1.10 myserver.local
```

и запустите клиент с использованием этого имени, чтобы продемонстрировать поиск по DNS-имени.

**Чек-лист перед выходом на защиту**
- Сборка проекта — без ошибок.
- Firewall: откройте порты TCP/UDP или временно отключите Firewall.
- 4 клиента готовы (на 2+ машинах или в 4 окнах).
- `timeOutDisconnect` = 180 проверено и пересобрано.
- Hosts/DNS настроен для демонстрации DNS-имени.
- Логи видны (окон сервера/консоли) — подготовьте скриншоты/файлы логов на случай проблем.

Если хотите, могу подготовить готовый патч, который автоматически установит `timeOutDisconnect = 180` и добавит в `README.md` примеры команд запуска с путями к exe (или могу выписать точные строки, которые вы будете показывать в презентации). Скажи, что делаем дальше.
