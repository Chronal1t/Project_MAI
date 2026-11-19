#include <iostream>
#include <fstream>
#include <string>
#include "tasks.h"
#include "http.h"
#include "server.h"
#include "router.h"

using namespace std;

//  ОБРАБОТЧИКИ (КОНТРОЛЛЕРЫ) 

HttpResponse handleGetRoot(const HttpRequest& req) {
    HttpResponse res;
    ifstream file("../frontend/index.html");
    res.body = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    if (res.body.empty()) {
        res.statusCode = 404;
        res.body = "<h1>404 File not found</h1>";
    }
    return res;
}

HttpResponse handleGetCss(const HttpRequest& req) {
    HttpResponse res;
    res.contentType = "text/css";
    ifstream file("../frontend/style.css");
    res.body = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    if (res.body.empty()) res.body = "/* not found */";
    return res;
}

HttpResponse handleGetTasks(const HttpRequest& req) {
    HttpResponse res;
    res.contentType = "application/json";
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
    
    res.body = getTasksJson(results, count);
    return res;
}

HttpResponse handlePostTasks(const HttpRequest& req) {
    HttpResponse res;
    res.contentType = "application/json";
    
    string title = req.getFormParam("title");
    string priorityStr = req.getFormParam("priority");
    string deadline = req.getFormParam("deadline");

    if (!title.empty() && !priorityStr.empty() && taskCount < MAX_TASKS) {
        tasks[taskCount].id = nextId++;
        tasks[taskCount].title = title;
        tasks[taskCount].priority = stoi(priorityStr);
        tasks[taskCount].deadline = deadline.empty() ? "Не указан" : deadline;
        tasks[taskCount].status = "todo";
        taskCount++;
        res.body = "{\"status\":\"ok\"}";     
    } else {
        res.statusCode = 400;
        res.body = "{\"error\":\"Bad Request\"}";     
    }
    return res;
}

HttpResponse handleDeleteTask(const HttpRequest& req) {
    HttpResponse res;
    res.contentType = "application/json";
    
    string idStr = req.path.substr(11); 
    int idToDelete = 0;
    try {
        idToDelete = stoi(idStr); 
    } catch (...) {
        res.statusCode = 400;
        res.body = "{\"error\":\"Invalid ID\"}";
        return res;
    }

    if (idToDelete > 0) {
        bool success = deleteTaskById(idToDelete);
        if (success) {
            res.body = "{\"status\":\"deleted\"}";
        } else {
            res.statusCode = 404;
            res.body = "{\"status\":\"not found\"}";
        }
    }
    return res;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    // Инициализация данных
    tasks[0] = {nextId++, "Купить молоко", 1, "2026-11-10", "todo"};
    tasks[1] = {nextId++, "Выучить сокеты", 5, "2026-11-15", "todo"};
    taskCount = 2;

    SocketServer server(8080);
    if (!server.start()) {
        return 1;
    }

    Router router;
    router.add("GET", "/", handleGetRoot);
    router.add("GET", "/style.css", handleGetCss);
    router.add("GET", "/api/tasks", handleGetTasks);
    router.add("POST", "/api/tasks", handlePostTasks);
    // DELETE мы обрабатываем отдельно, так как там динамический ID

    while (true) {
        SOCKET client = server.acceptClient();
        if (client == INVALID_SOCKET) continue;

        HttpRequest req = server.receiveRequest(client);
        cout << "[" << req.method << "] " << req.path << endl;

        HttpResponse res;
        
        // Проверяем DELETE с ID
        if (req.method == "DELETE" && req.path.find("/api/tasks/") == 0) {
            res = handleDeleteTask(req);
        } else {
            res = router.dispatch(req);
        }

        server.sendResponse(client, res);
    }

    server.stop();
    return 0;
}