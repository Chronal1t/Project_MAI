#include "Search.h"

using namespace std; 


string Search::normalize(const string& s) {
    if (s.empty())
    {
        return ""; // Если строка пустая, сразу выходим
    }
    string res = s;
    
    // 1. Ищем пробелы в начале
    int start = 0;
    while (start < res.length() && (res[start] == ' ' || res[start] == '\t' || res[start] == '\n' || res[start] == '\r'))
    {
        start++;
    }
    
    // Если вся строка состоит из пробелов
    if (start == res.length()) 
    {
        return "";
    }
    
    // 2. Ищем пробелы в конце
    int end = res.length() - 1;
    while (end >= start && (res[end] == ' ' || res[end] == '\t' || res[end] == '\n' || res[end] == '\r')) 
    {
        end--;
    }
    
    // 3. Собираем новую строку (от start до end включительно)
    string result = "";
    for (int i = start; i <= end; i++)
    {
        // Перевод в нижний регистр
        char c = res[i];
        if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A'); // Превращаем 'A' в 'a'
        }
        result += c;
    }
    
    return result;
}

/*string Search::normalize(const string& s) {
    string res = s;
    
    size_t start = res.find_first_not_of(" \t\n\r");// ищем  первый символе !=" "
    if (start == string::npos)
    {
        return ""; 
    }

    res.erase(0, start);
    
    size_t end = res.find_last_not_of(" \t\n\r");
    res.erase(end + 1);
    
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}*/

vector<int> Search::linear_Search_By_Name(const vector<Task>& tasks, const string& word) {
    string needle = normalize(word);//приводим в нормальный вид
    vector<int> result;
    
    for (int  i = 0; i < tasks.size(); ++i) 
    {
        if (normalize(tasks[i].name).find(needle) != string::npos) 
        // проверяем наличие слова 
        {
            result.push_back(i);
        }
    }
    return result;
}


vector<int> Search::linear_Search_By_Human(const vector<Task>& tasks, int humanId) {
    vector<int> result;
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        if (tasks[i].id_human == humanId) 
        {
            result.push_back(static_cast<int>(i));
        }
    }
    return result;
}


vector<int> Search::linear_Search_By_Team(const vector<Task>& tasks, int teamId) {
    vector<int> result;
    for (size_t i = 0; i < tasks.size(); ++i) 
    {
        if (tasks[i].id_team == teamId)
        {
            result.push_back(static_cast<int>(i));
        }
    }
    return result;
}


int Search::linear_Search_By_Id(const vector<Task>& tasks, int targetId) 
{
    for (int i = 0; i < tasks.size(); ++i) 
    {
        if (tasks[i].id == targetId)
        {
            return i;
        }
    }
    return -1;
}

int Search::binary_Search_By_Id(const vector<Task>& sortedTasks, int targetId) {
    int left=0;
    int right =  sortedTasks.size() - 1; 
    
    while (left<= right)
     {
        int mid = left + ( right - left) / 2;
        if (sortedTasks[mid].id == targetId) 
        {
            return mid;
        }
        else if (sortedTasks[mid].id < targetId)
        {
            left = mid + 1;
        } 
        else 
        {
            right = mid - 1;
        } 
    }
    return -1;
}

int Search::binary_Search_By_NAME_Exact(const vector<Task>& sortedTasks, const string& name) {
    string target = normalize(name);
    int left=0;
    int right =  sortedTasks.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;

        string cur = normalize(sortedTasks[mid].name);
        if (cur == target)
        {
            return mid;
        }
        else if (cur < target)
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }
    return -1;
}