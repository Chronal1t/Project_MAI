#pragma once
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Search {
public:
    static string normalize(const string& s);
    
    static vector<int> linear_Search_By_Name(const vector<Task>& tasks, const string& word);

    static int linear_Search_By_Id(const vector<Task>& tasks, int targetId);

    static int binary_Search_By_Id(const vector<Task>& sortedTasks, int targetId);

    static int binary_Search_By_NAME_Exact(const vector<Task>& sortedTasks, const string& name);

    static vector<int> linear_Search_By_Human(const vector<Task>& tasks, int humanId);
    
    static vector<int> linear_Search_By_Team(const vector<Task>& tasks, int teamId);
};