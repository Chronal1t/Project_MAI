#pragma once
#include "models.h"
using namespace std;

bool deleteTaskById(int id);
string getTasksJson(Task arr[], int count);
string getFormValue(const string& body, const string& key);