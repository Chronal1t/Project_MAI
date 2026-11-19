#include "router.h"

void Router::add(const string& method, const string& path, Handler handler) {
    routes[method + " " + path] = handler;
}

HttpResponse Router::dispatch(const HttpRequest& req) {
    string key = req.method + " " + req.path;
    
    // Если такой маршрут зарегистрирован — вызываем его
    if (routes.find(key) != routes.end()) {
        return routes[key](req);
    }
    
    // Если нет — возвращаем 404
    HttpResponse res;
    res.statusCode = 404;
    res.contentType = "application/json";
    res.body = "{\"error\":\"Not Found\"}";
    return res;
}