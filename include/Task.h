#pragma once
#include <string>

using namespace std; 

struct Task {
    int id;
    string title;
    int priority;
    string deadline; // Формат "YYYY-MM-DD"
    string status;
};