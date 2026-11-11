#pragma once
#include <string>

using namespace std; 

struct Task {
    int id;
    string name;
    int priority;
    string deadline; // Формат "YYYY-MM-DD"
    string status;
    int id_team;
    int id_human;
};