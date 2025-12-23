Task28 - Dynamic accept ports demo

Server.exe (Server.cpp)
- Default listens on port 2000.
- Accepts console commands:
  - OPEN_ACCEPT <port>  -> start listening on that port
  - CLOSE_ACCEPT <port> -> stop listening on that port
  - exit -> stop server

Client.exe (Client.cpp)
- Usage: Client <server_ip> <port>
- Type messages, server echoes them.

Build: open Visual Studio, add files to a Win32 Console project or compile with cl.exe.
Example (Developer Command Prompt):
cl /EHsc /MD Server.cpp ws2_32.lib
cl /EHsc /MD Client.cpp ws2_32.lib
