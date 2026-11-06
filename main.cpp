#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h> 
#include <ws2tcpip.h>
#include "tasks.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {

    tasks[0] = {nextId++, "Купить молоко", 1, "2026-11-10", "todo"};
    tasks[1] = {nextId++, "Выучить сокеты", 5, "2026-11-15", "todo"};
    taskCount = 2;

    // Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed." << endl;
        return 1;
    }

    //сокет 
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    // localhost:8080
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Принимать подключения с любого IP
    serverAddr.sin_port = htons(8080);       // Порт 8080

    // bind
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Bind failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // listen
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listen failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server started on http://localhost:8080" << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) continue;

        char buffer[4096] = {0};
        recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        string request(buffer);

        // --- ПАРСИНГ ЗАПРОСА ---
        string firstLine = request.substr(0, request.find("\r\n"));
        string method, path, requestBody;
        size_t firstSpace = firstLine.find(' ');
        size_t secondSpace = firstLine.find(' ', firstSpace + 1);
        size_t bodyStart = request.find("\r\n\r\n");
        
        if (firstSpace != string::npos && secondSpace != string::npos) {
            method = firstLine.substr(0, firstSpace);
            path = firstLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            cout << "Method: " << method << " | Path: " << path << endl;
        }

        if (bodyStart != string::npos) {
            requestBody = request.substr(bodyStart + 4);
            cout << requestBody << endl;
        }

        string response;
        string contentType = "text/html; charset=utf-8";
        string body = "";

        // РОУТИНГ 
        if (method == "GET" && path == "/") {
            ifstream file("index.html");
            body = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
            if (body.empty()) body = "<h1>404 File not found</h1>";

        }else if (method == "GET" && path == "/style.css") {
            ifstream file("style.css");
            body = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
            contentType = "text/css";
            if (body.empty()) body = "/* not found */";

        }else if (method == "GET" && path == "/api/tasks") {
            contentType = "application/json";
            body = getTasksJson(tasks, taskCount);

        }else if(method == "POST" && path == "/api/tasks") {
            string title = getFormValue(requestBody, "title");
            string priorityStr = getFormValue(requestBody, "priority");
            string deadline = getFormValue(requestBody, "deadline");
            if (!title.empty() && !priorityStr.empty() && taskCount < MAX_TASKS) {
                tasks[taskCount].id = nextId++;
                tasks[taskCount].title = title;
                tasks[taskCount].priority = stoi(priorityStr);
                tasks[taskCount].deadline = deadline.empty() ? "Не указан" : deadline;
                tasks[taskCount].status = "todo";
                taskCount++;
                contentType = "application/json";
                body = "{\"status\":\"ok\"}";     
            } else {
                contentType = "application/json";
                body = "{\"status\":\"error\"}";     
                response = "HTTP/1.1 400 Bad Request\r\n";
            }

        } else if (method == "DELETE" && path.find("/api/tasks/") == 0) {
            string idStr = path.substr(11); 
            
            int idToDelete = 0;
            try {
                idToDelete = stoi(idStr); 
            } catch (...) {
                contentType = "application/json";
                body = "{\"error\":\"Invalid ID\"}";
                response = "HTTP/1.1 400 Bad Request\r\n";
            }

            if (idToDelete > 0) {
                bool success = deleteTaskById(idToDelete);
                contentType = "application/json";
                if (success) {
                    body = "{\"status\":\"deleted\"}";
                } else {
                    body = "{\"status\":\"not found\"}";
                    response = "HTTP/1.1 404 Not Found\r\n";
                }
            }
        } else {
            contentType = "text/plain";
            body = "404 Not Found";
            response = "HTTP/1.1 404 Not Found\r\n";
        }

        // Формируем HTTP-ответ
        if (response.empty()) { 
            response = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: " + contentType + "\r\n"
                       "Content-Length: " + to_string(body.length()) + "\r\n"
                       "Connection: close\r\n"
                       "\r\n" + body;
        } else {
            response += "Content-Type: " + contentType + "\r\n"
                        "Content-Length: " + to_string(body.length()) + "\r\n"
                        "Connection: close\r\n"
                        "\r\n" + body;
        }

        send(clientSocket, response.c_str(), response.length(), 0);
        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}