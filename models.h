#pragma once // Защита от двойного включения
#include <string>

using namespace std;

struct Task {
    int id;
    string title;
    int priority;
    string deadline;
    string status;
};

const int MAX_TASKS = 1000;

extern Task tasks[MAX_TASKS];
extern int taskCount;
extern int nextId;