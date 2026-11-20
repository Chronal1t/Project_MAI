#pragma once
#include <string>

struct Task
{
    int id;
    std::string name;
    int priority;
    bool status; 
    std::string deadline;
    int id_human;
    int id_team;
    int addiction_id;
}; // Task

void SWAP(Task* Arg1, int Arg2, int Arg3);
int type_to_code(int Arg1);
int translate_to_number(std::string Arg1);
int getattr_int(Task &Arg1, int Arg2);
std::string getattr_string(Task &Arg1, int Arg2);
bool getattr_bool(Task &Arg1, int Arg2);
int Partition(Task* Arg1, std::string Arg2, int Arg3, int Arg4, bool Arg5);
void QuickSort_start(Task* Arg1, std::string Arg2, int Arg3, int Arg4, bool Arg5);
void QuickSort(Task* Arg1, std::string Arg2, int Arg3, bool Arg4);
void InsertionSort(Task* Arg1, std::string Arg2, int Arg3, bool Arg4);
void Merge(Task* Arg1, std::string Arg2, int Arg3, int Arg4, int Arg5, bool Arg6);
void MergeSort(Task* Arg1, std::string Arg2, int Arg3, bool Arg4);
void Merge_sort_start(Task* Arg1, std::string Arg2, int Arg3, int Arg4, bool Arg5);