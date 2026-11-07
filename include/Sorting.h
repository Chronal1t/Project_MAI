#pragma once
#include <vector>
#include "Task.h"

// Поля, по которым можно сортировать
enum class SortField { 
    ID, 
    PRIORITY, 
    TITLE, 
    DEADLINE 
};

// Этот интерфейс должен будет реализовать 4-й участник
// (или мы используем его для заглушки)
class ISorter {
public:
    virtual ~ISorter() = default;
    virtual void sort(std::vector<Task>& tasks, SortField field) = 0;
};