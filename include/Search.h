#pragma once
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Search {
public:
    static string normalize(const string& s);
    
    static vector<int> linear_Search_By_Title(const vector<Task>& tasks, const string& word);

    static int linear_Search_By_Id(const vector<Task>& tasks, int targetId);

    static int binary_Search_By_Id(const vector<Task>& sortedTasks, int targetId);

    static int binary_Search_By_Title_Exact(const vector<Task>& sortedTasks, const string& title);
};