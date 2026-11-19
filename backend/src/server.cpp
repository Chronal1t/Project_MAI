#include "server.h"
#include <iostream>

using namespace std;

// Конструктор
SocketServer::SocketServer(int p) {
    port = p;
    serverSocket = INVALID_SOCKET;
}

// Метод start (должен возвращать bool)
bool SocketServer::start() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) return false;
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) return false;
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) return false;
    
    cout << "Server started on http://localhost:" << port << endl;
    return true;
}

// Метод acceptClient
SOCKET SocketServer::acceptClient() {
    return accept(serverSocket, nullptr, nullptr);
}

// Метод receiveRequest (должен возвращать HttpRequest)
HttpRequest SocketServer::receiveRequest(SOCKET clientSocket) {
    char buffer[8192] = {0};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytesRead <= 0) {
        return HttpRequest(); // Возвращаем пустой запрос, если не удалось прочитать
    }
    
    string raw(buffer, bytesRead);
    return parseHttpRequest(raw);
}

// Метод sendResponse
void SocketServer::sendResponse(SOCKET clientSocket, const HttpResponse& res) {
    string response = res.toString();
    send(clientSocket, response.c_str(), response.length(), 0);
    closesocket(clientSocket);
}

// Метод stop
void SocketServer::stop() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
}