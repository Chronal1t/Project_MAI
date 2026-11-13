#pragma once
#include <string>

using namespace std; 

struct Task {
    int id;// ID
    string name;//имя
    int priority;//приоритет 
    string deadline; // Формат "YYYY-MM-DD"
    string status;//статус
    int id_team; //ID команды
    int id_human;// ID человека
    int addiction_id;//зависимость одной задачи  от другой
};