
#pragma once
#include <string>
#include "Task.h"

using namespace std;

class Search {
public:
    static string normalize(const string& s);

    static int* linear_Search_By_Name(const Task* tasks, int size,const string& word, int& count);

    static int linear_Search_By_Id(const Task* tasks, int size, int targetId);

    static int binary_Search_By_Id(const Task* sortedTasks, int size, int targetId);

    static int binary_Search_By_NAME_Exact(const Task* sortedTasks, int size,const string& name);

    static int* linear_Search_By_Human(const Task* tasks, int size,int humanId, int& count);

    static int* linear_Search_By_Team(const Task* tasks, int size,int teamId, int& count);
};