#include "http.h"
#include <string>
#include <map>
#include <sstream>
#include <cctype>

using namespace std;

string urlDecode(const string& str) {
    string result;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '+') {
            result += ' ';
        } else if (str[i] == '%' && i + 2 < str.length()) {
            string hex = str.substr(i + 1, 2);
            char ch = (char)strtol(hex.c_str(), nullptr, 16);
            result += ch;
            i += 2;
        } else {
            result += str[i];
        }
    }
    return result;
}

string extractParam(const string& source, const string& key) {
    string searchKey = key + "=";
    size_t pos = source.find(searchKey);
    if (pos == string::npos) return "";
    size_t startPos = pos + searchKey.length();
    size_t endPos = source.find('&', startPos);
    if (endPos == string::npos) endPos = source.length();
    return urlDecode(source.substr(startPos, endPos - startPos));
}

string HttpRequest::getQueryParam(const string& key) const {
    return extractParam(query, key);
}

string HttpRequest::getFormParam(const string& key) const {
    return extractParam(body, key);
}

string HttpResponse::toString() const {
    string statusText;
    switch(statusCode) {
        case 200: statusText = "OK"; break;
        case 201: statusText = "Created"; break;
        case 400: statusText = "Bad Request"; break;
        case 401: statusText = "Unauthorized"; break;
        case 404: statusText = "Not Found"; break;
        case 409: statusText = "Conflict"; break;
        case 500: statusText = "Internal Server Error"; break;
        default: statusText = "Unknown Error"; break;
    }
    ostringstream os;
    os << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";
    os << "Content-Type: " << contentType << "\r\n";
    os << "Content-Length: " << to_string(body.length()) << "\r\n";
    os << "Connection: close\r\n";
    os << "\r\n";
    os << body;

    return os.str();
}

HttpRequest parseHttpRequest(const string& raw) {
    HttpRequest req;
    size_t firstLineEnd = raw.find("\r\n");
    string firstLine = raw.substr(0, firstLineEnd);

    size_t firstSpace = firstLine.find(' ');
    size_t secondSpace = firstLine.find(' ', firstSpace + 1);
    req.method = firstLine.substr(0, firstSpace);
    string pathAndQuery = firstLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);

    size_t qPos = pathAndQuery.find('?');
    if (qPos != string::npos) {
        req.path = pathAndQuery.substr(0, qPos); 
        req.query = pathAndQuery.substr(qPos + 1); 
    } else {
        req.path = pathAndQuery; 
        req.query = "";
    }

    size_t bodyStart = raw.find("\r\n\r\n");
    if (bodyStart != string::npos) {
        req.body = raw.substr(bodyStart + 4); 
    } else {
        req.body = "";
    }

    return req;
}