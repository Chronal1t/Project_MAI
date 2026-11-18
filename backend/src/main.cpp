#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h> 
#include <ws2tcpip.h>
#include "tasks.h"
#include "http.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {

    // Инициализация стартовых задач
    tasks[0] = {nextId++, "Купить молоко", 1, "2026-11-10", "todo"};
    tasks[1] = {nextId++, "Выучить сокеты", 5, "2026-11-15", "todo"};
    taskCount = 2;

    // Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed." << endl;
        return 1;
    }

    // Создание сокета
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    // localhost:8080
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

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

        // Читаем запрос. Делаем буфер побольше, на случай длинных POST-запросов.
        char buffer[8192] = {0};
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytesRead <= 0) {
            closesocket(clientSocket);
            continue;
        }

        string rawRequest(buffer, bytesRead);
        HttpRequest req = parseHttpRequest(rawRequest);
        
        // Логируем каждый входящий запрос в консоль
        cout << "[" << req.method << "] " << req.path << endl;
        if (!req.body.empty()) {
            cout << "   Body: " << req.body << endl;
        }

        string response;
        string contentType = "text/html; charset=utf-8";
        string body = "";

        // РОУТИНГ
        if (req.method == "GET" && req.path == "/") {
            ifstream file("../frontend/index.html");
            body = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
            if (body.empty()) body = "<h1>404 File not found</h1>";

        } else if (req.method == "GET" && req.path == "/style.css") {
            ifstream file("../frontend/style.css");
            body = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
            contentType = "text/css";
            if (body.empty()) body = "/* not found */";

        } else if (req.method == "GET" && req.path == "/api/tasks") {
            contentType = "application/json";
            Task results[MAX_TASKS];
            int count = 0;
            
            string q = req.getQueryParam("q");
            string statusStr = req.getQueryParam("status");
            string priorityStr = req.getQueryParam("priority");

            if (!q.empty()) {
                count = searchTasksByTitle(tasks, taskCount, q, results);
            } else {
                int priority = 0;
                if (!priorityStr.empty()) {
                    try { priority = stoi(priorityStr); } catch(...) {}
                }
                count = filterTasks(tasks, taskCount, statusStr, priority, results);
            }
            body = getTasksJson(results, count);

        } else if (req.method == "POST" && req.path == "/api/tasks") {
            // Теперь парсим данные из формы
            string title = req.getFormParam("title");
            string priorityStr = req.getFormParam("priority");
            string deadline = req.getFormParam("deadline");
            
            cout << "   Parsed Title: [" << title << "], Priority: [" << priorityStr << "]" << endl;

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
                body = "{\"error\":\"Bad Request\"}";     
                response = "HTTP/1.1 400 Bad Request\r\n";
            }

        } else if (req.method == "DELETE" && req.path.find("/api/tasks/") == 0) {
            // Извлекаем ID из пути (например, "/api/tasks/3" -> "3")
            string idStr = req.path.substr(11); 
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