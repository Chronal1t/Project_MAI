#include "Sort.h"
#include <iostream>

using namespace std;

void SWAP(Task* Arg1, int Arg2, int Arg3)
{
    Task temp = Arg1[Arg2];
    Arg1[Arg2] = Arg1[Arg3];
    Arg1[Arg3] = temp;
}// SWAP

int type_to_code(int Arg1)
{
    //1 - int
    //2 - string
    //3 - bool
    switch (Arg1)
    {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 1;
    case 3:
        return 3;
    case 4:
        return 2;
    case 5:
        return 1;
    case 6:
        return 1;
    case 7:
        return 1;
    default:
        return -1;
    }//switch
}//type_to_code

int translate_to_number(std::string Arg1)
{
    if (Arg1 == "id")
    {
        return 0;
    }// if
    if (Arg1 == "name")
    {
        return 1;
    }// if
    if (Arg1 == "priority")
    {
        return 2;
    }// if
    if (Arg1 == "status")
    {
        return 3;
    }// if
    if (Arg1 == "deadline")
    {
        return 4;
    }// if
    if (Arg1 == "id_human")
    {
        return 5;
    }// if
    if (Arg1 == "id_team")
    {
        return 6;
    }// if
    if (Arg1 == "addiction_id")
    {
        return 7;
    }// if
    return -1;
}// translate_to_number

int getattr_int(Task &Arg1, int Arg2)
{
    switch (Arg2)
    {
    case 0:
        return Arg1.id;
    case 2:
        return Arg1.priority;
    case 5:
        return Arg1.id_human;
    case 6:
        return Arg1.id_team;
    }//switch
}//getattr_int

std::string getattr_string(Task &Arg1, int Arg2)
{
    switch (Arg2)
    {
    case 1:
        return Arg1.name;
    case 4:
        return Arg1.deadline;
    }//switch
}//getattr_string

bool getattr_bool(Task &Arg1, int Arg2)
{
    return Arg1.status;
}//bool getattr_bool

int Partition(Task* Arg1, string Arg2, int Arg3, int Arg4, bool Arg5)
{
    Task pivot = Arg1[(Arg3+Arg4)/2];
    SWAP(Arg1, (Arg3+Arg4)/2, Arg4);
    int q = Arg3;
    int type = type_to_code(translate_to_number(Arg2));
    if(Arg5)
    {
        for (int u = Arg3; u < Arg4; u++)
        {
            switch (type)
            {
            case 1 :
                if (getattr_int(Arg1[u], translate_to_number(Arg2)) <= getattr_int(pivot, translate_to_number(Arg2)))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 2 :
                if (getattr_string(Arg1[u], translate_to_number(Arg2)) <= getattr_string(pivot, translate_to_number(Arg2)))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 3 :
                if (getattr_bool(Arg1[u], translate_to_number(Arg2)) <= getattr_bool(pivot, translate_to_number(Arg2)))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            }//switch
        }// for u
    }//if
    else
    {
        for (int u = Arg3; u < Arg4; u++)
        {
            switch (type)
            {
            case 1 :
                if (getattr_int(Arg1[u], translate_to_number(Arg2)) >= getattr_int(pivot, translate_to_number(Arg2)))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 2 :
                if (getattr_string(Arg1[u], translate_to_number(Arg2)) >= getattr_string(pivot, translate_to_number(Arg2)))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 3 :
                if (getattr_bool(Arg1[u], translate_to_number(Arg2)) >= getattr_bool(pivot, translate_to_number(Arg2)))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            }//switch
        }// for u        
    }//else
    SWAP(Arg1, q, Arg4);
    return q;
}// Partition


void QuickSort(Task* Arg1, string Arg2, int Arg3, int Arg4, bool Arg5)
{
    if (Arg3 >= Arg4)
    {
        return ;
    }// if
    
    int q = Partition(Arg1, Arg2, Arg3, Arg4, Arg5);
    QuickSort(Arg1, Arg2, Arg3, q-1, Arg5);
    QuickSort(Arg1, Arg2, q+1, Arg4, Arg5);
}// QuickSort


Task* InsertionSort(Task* Arg1, string Arg2, bool Arg3)
{
    //Arg1 - Список задач
    //Arg2 - Ключ
    //Arg3 - (1-возрастание, 0 - убывание)
    
    return Arg1;
}//InsertionSort