

#pragma once
#include "Task.h"

// Поля, по которым можно сортировать
enum class SortField {
    ID,
    PRIORITY,
    NAME,
    DEADLINE
};

// Этот интерфейс должен будет реализовать 4-й участник
// (или мы используем его для заглушки)
class ISorter {
public:
    virtual ~ISorter() = default;
    virtual void sort(Task* tasks, int size, SortField field) = 0;
};