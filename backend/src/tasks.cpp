#include "tasks.h"

Task tasks[MAX_TASKS];
int taskCount = 0;
int nextId = 1;

bool deleteTaskById(int id) {
    for (int i = 0; i < taskCount; i++) {
        if(tasks[i].id == id) {
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            taskCount--;
            return true;
        }
    }
    return false;
}

string getTasksJson(Task arr[], int count) {
    if (count == 0) return "[]";

    string json = "[";
    for (int i = 0; i < count; i++) {
        json += "{\"id\":" + to_string(arr[i].id) + 
                ",\"title\":\"" + arr[i].title + 
                "\",\"priority\":" + to_string(arr[i].priority) + 
                ",\"deadline\":\"" + arr[i].deadline + 
                "\",\"status\":\"" + arr[i].status + "\"}";
        
        if (i < count - 1) json += ",";
    }
    json += "]";
    return json;
}

string getFormValue(const string& body, const string& key) {
    string searchKey = key + "=";
    size_t pos = body.find(searchKey);
    if (pos == string::npos) return "";
    pos += searchKey.length();
    size_t endPos = body.find('&', pos);
    if (endPos == string::npos) endPos = body.length();
    return body.substr(pos, endPos - pos);
}

int searchTasksByTitle(Task arr[], int count, const string& query, Task result[]) {
    int foundCount = 0;
    for (int i =0; i < count; i++) {
        if (arr[i].title.find(query) != string::npos) {
            result[foundCount] = arr[i];
            foundCount++;
        }
    }
    return foundCount;
}

int filterTasks(Task arr[], int count, const string& status, int priority, Task result[]) {
    int foundCount = 0;
    for (int i =0; i < count; i++) {
        if (!status.empty() && arr[i].status != status) continue;
        if (priority > 0 && arr[i].priority != priority) continue;
        result[foundCount] = arr[i];
    }
    return foundCount;
}