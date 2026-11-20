#include "Sort.h"
#include <iostream>

using namespace std;

#define INFINITY 1000000000


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
    int number = translate_to_number(Arg2);
    int type = type_to_code(number);
    if(Arg5)
    {
        for (int u = Arg3; u < Arg4; u++)
        {
            switch (type)
            {
            case 1 :
                if (getattr_int(Arg1[u], number) <= getattr_int(pivot, number))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 2 :
                if (getattr_string(Arg1[u], number) <= getattr_string(pivot, number))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 3 :
                if (getattr_bool(Arg1[u], number) <= getattr_bool(pivot, number))
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
                if (getattr_int(Arg1[u], number) >= getattr_int(pivot, number))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 2 :
                if (getattr_string(Arg1[u], number) >= getattr_string(pivot, number))
                {
                    SWAP(Arg1, q, u);
                    q++;
                }// if
                break;
            case 3 :
                if (getattr_bool(Arg1[u], number) >= getattr_bool(pivot, number))
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


void QuickSort_start(Task* Arg1, string Arg2, int Arg3, int Arg4, bool Arg5)
{
    if (Arg3 >= Arg4)
    {
        return ;
    }// if
    
    int q = Partition(Arg1, Arg2, Arg3, Arg4, Arg5);
    QuickSort_start(Arg1, Arg2, Arg3, q-1, Arg5);
    QuickSort_start(Arg1, Arg2, q+1, Arg4, Arg5);
}// QuickSort_start

void QuickSort(Task* Arg1, std::string Arg2, int Arg3, bool Arg4)
{
    QuickSort_start(Arg1, Arg2, 0, Arg3-1, Arg4);
}// QuickSort



void InsertionSort(Task* Arg1, string Arg2, int Arg3, bool Arg4)
{
    //Arg1 - Список задач
    //Arg2 - Ключ
    //Arg3 - размер массива
    //Arg4 - (1-возрастание, 0 - убывание)
    int number = translate_to_number(Arg2);
    int type = type_to_code(number);
    int j;
    Task key;
    if (Arg4)
    {
        for (int i = 1; i < Arg3; i++)
        {
            key = Arg1[i];
            j = i-1;
            while (j >= 0)
            {
                switch (type)
                {
                case 1 :
                    if (getattr_int(Arg1[j], number) > getattr_int(key, number))
                    {
                        Arg1[j+1] = Arg1[j];
                        j--;
                    }// if
                    break;
                case 2 :
                    if (getattr_string(Arg1[j], number) > getattr_string(key, number))
                    {
                        Arg1[j+1] = Arg1[j];
                        j--;
                    }// if
                    break;
                case 3 :
                    if (getattr_bool(Arg1[j], number) > getattr_bool(key, number))
                    {
                        Arg1[j+1] = Arg1[j];
                        j--;
                    }// if
                    break;
                }//switch 
            }// while
            Arg1[j+1] = key;
        }// for i
    }// if
    else
    {
        for (int i = 1; i < Arg3; i++)
        {
            key = Arg1[i];
            j = i-1;
            while (j >= 0)
            {
                switch (type)
                {
                case 1 :
                    if (getattr_int(Arg1[j], number) < getattr_int(key, number))
                    {
                        Arg1[j+1] = Arg1[j];
                        j--;
                    }// if
                    break;
                case 2 :
                    if (getattr_string(Arg1[j], number) < getattr_string(key, number))
                    {
                        Arg1[j+1] = Arg1[j];
                        j--;
                    }// if
                    break;
                case 3 :
                    if (getattr_bool(Arg1[j], number) < getattr_bool(key, number))
                    {
                        Arg1[j+1] = Arg1[j];
                        j--;
                    }// if
                    break;
                }//switch 
            }// while
            Arg1[j+1] = key;
        }// for i
    }//else
}//InsertionSort


void Merge_sort_start(Task* Arg1, string Arg2, int Arg3, int Arg4, bool Arg5)
{
    if (Arg3 >= Arg4)
    {
        return ;
    }// if

    int q = (Arg4+Arg3)/2;
    Merge_sort_start(Arg1, Arg2, Arg3,q, Arg5);
    Merge_sort_start(Arg1, Arg2, 1+q, Arg4, Arg5);
    Merge(Arg1, Arg2, Arg3, q, Arg4, Arg5);

}//Merge_sort_start

void Merge(Task* Arg1, string Arg2, int Arg3, int Arg4, int Arg5, bool Arg6)
{
    int n1 = Arg4 - Arg3 + 1; 
    int n2 = Arg5 - Arg4;     
    int type = type_to_code(translate_to_number(Arg2));
    int number = translate_to_number(Arg2);
    Task B[n1+1];
    Task C[n2+1];

    Task Dop_max, Dop_min;
    Dop_max.id = INFINITY;
    Dop_max.priority = INFINITY;
    Dop_max.id_human = INFINITY;
    Dop_max.addiction_id = INFINITY;
    Dop_max.id_team = INFINITY;
    Dop_max.status = true;
    Dop_max.deadline = "9999999-12-31";
    Dop_max.name = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    
    Dop_min.id = -INFINITY;
    Dop_min.priority = -INFINITY;
    Dop_min.id_human = -INFINITY;
    Dop_min.addiction_id = -INFINITY;
    Dop_min.id_team = -INFINITY;
    Dop_min.status = false;
    Dop_min.deadline = "0000-00-00";
    Dop_min.name = "AAAAAAAAAAAAAAAAAAAAAAAAAAA";


    for (int k = 0; k < n1; k++)
    {
        B[k] = Arg1[Arg3 + k];
    }
    
    for (int k = 0; k < n2; k++)
    {
        C[k] = Arg1[Arg4 + 1 + k];
    }
    
    int i = 0;
    int j = 0;

    if (Arg6)
    {
        B[n1] = Dop_max;
        C[n2] = Dop_max;
        for (int k = Arg3; k <= Arg5; k++)
        {   
            switch(type)
            {
                case 1:
                    if(getattr_int(B[i], number) <= getattr_int(C[j], number))
                    {
                        Arg1[k] = B[i];
                        i+=1;
                    }// if
                    else
                    {
                        Arg1[k] = C[j];
                        j+=1;
                    }// else
                    break;
                case 2:
                    if(getattr_string(B[i], number) <= getattr_string(C[j], number))
                    {
                        Arg1[k] = B[i];
                        i+=1;
                    }// if
                    else
                    {
                        Arg1[k] = C[j];
                        j+=1;
                    }// else
                    break;
                case 3:
                    if(getattr_bool(B[i], number) <= getattr_bool(C[j], number))
                    {
                        Arg1[k] = B[i];
                        i+=1;
                    }// if
                    else
                    {
                        Arg1[k] = C[j];
                        j+=1;
                    }// else
                    break;
            }// switch
        }// for k
    }//if
    else
    {
        B[n1] = Dop_min;
        C[n2] = Dop_min;
        for (int k = Arg3; k <= Arg5; k++)
        {   
            switch(type)
            {
                case 1:
                    if(getattr_int(B[i], number) >= getattr_int(C[j], number))
                    {
                        Arg1[k] = B[i];
                        i+=1;
                    }// if
                    else
                    {
                        Arg1[k] = C[j];
                        j+=1;
                    }// else
                    break;
                case 2:
                    if(getattr_string(B[i], number) >= getattr_string(C[j], number))
                    {
                        Arg1[k] = B[i];
                        i+=1;
                    }// if
                    else
                    {
                        Arg1[k] = C[j];
                        j+=1;
                    }// else
                    break;
                case 3:
                    if(getattr_bool(B[i], number) >= getattr_bool(C[j], number))
                    {
                        Arg1[k] = B[i];
                        i+=1;
                    }// if
                    else
                    {
                        Arg1[k] = C[j];
                        j+=1;
                    }// else
                    break;
            }// switch
        }// for k
    }// else
}//Merge


void MergeSort(Task* Arg1, string Arg2, int Arg3, bool Arg4)
{
    Merge_sort_start(Arg1, Arg2, 0, Arg3-1, Arg4);
}//MergeSort