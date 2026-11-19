#pragma once
#include <string>
#include <map>
#include <functional>
#include "http.h"

using namespace std;

class Router {
public:
    using Handler = function<HttpResponse(const HttpRequest&)>;
    
    void add(const string& method, const string& path, Handler handler);
    HttpResponse dispatch(const HttpRequest& req);

private:
    map<string, Handler> routes;
};