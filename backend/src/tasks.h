#pragma once
#include "models.h"
using namespace std;

bool deleteTaskById(int id);
string getTasksJson(Task arr[], int count);
string getFormValue(const string& body, const string& key);

int searchTasksByTitle(Task arr[], int count, const string& query, Task result[]);
int filterTasks(Task arr[], int count, const string& status, int priority, Task result[]);