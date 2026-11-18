#pragma once
#include <string>
#include <map>

using namespace std;

struct HttpRequest {
    string method;
    string path;
    string query;
    string body;
    string getQueryParam(const string& key) const;
    string getFormParam(const string& key) const; 
};

struct HttpResponse {
    int statusCode = 200;
    string contentType = "text/html; charset=utf-8";
    string body;
    string toString() const;
};

HttpRequest parseHttpRequest(const string& raw);