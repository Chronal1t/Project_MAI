#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winsock2.h>
#include <ws2tcpip.h>
#include "http.h"

using namespace std;

class SocketServer {
private:
    SOCKET serverSocket;
    int port;

public:
    SocketServer(int port);
    bool start();
    void stop();
    
    SOCKET acceptClient();
    HttpRequest receiveRequest(SOCKET clientSocket);
    void sendResponse(SOCKET clientSocket, const HttpResponse& res); // <--- ВОТ ЭТА СТРОКА
};