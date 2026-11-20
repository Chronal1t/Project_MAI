#include <iostream>
#include "Sort.h"
using namespace std;

#define N 10

Task Create_Task(int Arg1, string Arg2, int Arg3, bool Arg4, string Arg5, int Arg6, int Arg7, int Arg8)
{
    Task t;
    t.id = Arg1;
    t.name = Arg2;
    t.priority = Arg3;
    t.status= Arg4; 
    t.deadline= Arg5;
    t.id_human= Arg6;
    t.id_team= Arg7;
    t.addiction_id= Arg8;
    return t;
}// Create_Task

void Print_Task(Task* A, int size)
{
    for (int i =0 ; i  < size; i++)
    {
        cout << "Task " 
             << A[i].id << ' ' 
             << A[i].name << ' '
             << A[i].priority << ' '
             << A[i].status << ' ' 
             << A[i].deadline << ' '
             << A[i].id_human << ' '
             << A[i].id_team << ' '
             << A[i].addiction_id << endl;
    }// for i
    
}// Print_Task

int main()
{
    Task List[N] ={
        Create_Task( 7, "gamma",  2, true,  "2024-07-07", 70, 700, 1 ),
        Create_Task( 3, "alpha",  1, false, "2024-03-03", 30, 300, 3 ),
        Create_Task( 9, "iota",   3, true,  "2024-09-09", 90, 900, 4 ),
        Create_Task( 1, "beta",   2, false, "2024-01-01", 10, 100, 1 ),
        Create_Task( 5, "delta",  1, true,  "2024-05-05", 50, 500, 5 ),
        Create_Task( 8, "theta",  3, false, "2024-08-08", 80, 800, 8 ),
        Create_Task( 2, "epsilon",2, true,  "2024-02-02", 20, 200, 2 ),
        Create_Task( 6, "zeta",   1, false, "2024-06-06", 60, 600, 6 ),
        Create_Task(10, "kappa",  3, true,  "2024-10-10", 100,1000,1 ),
        Create_Task( 4, "eta",    2, false, "2024-04-04", 40, 400, 4 )
    };

    QuickSort(List, "id", N, 1);
    Print_Task(List, N);
    QuickSort(List, "name", N, 1);
    Print_Task(List, N);
    QuickSort(List, "priority", N, 1);
    Print_Task(List, N);
    QuickSort(List, "status", N, 1);
    Print_Task(List, N);
    QuickSort(List, "deadline", N, 1);
    Print_Task(List, N);
    QuickSort(List, "id_human", N, 1);
    Print_Task(List, N);
    QuickSort(List, "id_team", N, 1);
    Print_Task(List, N);
    QuickSort(List, "addiction_id", N, 1);
    Print_Task(List, N);

    cout <<'\n';
    InsertionSort(List, "id", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "name", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "priority", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "status", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "deadline", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "id_human", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "id_team", N, 1);
    Print_Task(List, N);
    InsertionSort(List, "addiction_id", N, 1);
    Print_Task(List, N);

    cout <<'\n';
    MergeSort(List, "id", N, 1);
    Print_Task(List, N);
    MergeSort(List, "name", N, 1);
    Print_Task(List, N);
    MergeSort(List, "priority", N, 1);
    Print_Task(List, N);
    MergeSort(List, "status", N, 1);
    Print_Task(List, N);
    MergeSort(List, "deadline", N, 1);
    Print_Task(List, N);
    MergeSort(List, "id_human", N, 1);
    Print_Task(List, N);
    MergeSort(List, "id_team", N, 1);
    Print_Task(List, N);
    MergeSort(List, "addiction_id", N, 1);
    Print_Task(List, N);
    return 0;
}// main