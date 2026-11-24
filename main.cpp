
/*g++ -O2 -Iinclude src/Search.cpp src/BST.cpp main.cpp -o bench_app*/
/*./bench_app.exe*/



#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include "Task.h"
#include "Search.h"
#include "BST.h"

using namespace std;
using namespace std::chrono;

// Функция для генерации случайных задач
Task* generateRandomTasks(int n) {
    Task* tasks = new Task[n];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> idDist(1, 1000000);
    uniform_int_distribution<> prioDist(1, 5);

    for (int i = 0; i < n; ++i) {
        Task& t = tasks[i];
        t.id = idDist(gen);
        t.name = "Task " + to_string(i);
        t.priority = prioDist(gen);
        t.deadline = "2026-01-01";
        t.status = "todo";
        t.id_team = 1;
        t.id_human = 1;
        t.addiction_id = 0;
    }
    return tasks;
}

int main() {
    const int sizes[] = {100, 500, 1000, 5000, 10000, 50000};

    cout << "Size\tLinear(ms)\tBinary(ms)\tBST(ms)\tFullSort(ms)\n";
    cout << "------------------------------------------------------------------------\n";

    for (int n : sizes) {
        Task* tasks = generateRandomTasks(n);

        // --- 1. ЛИНЕЙНЫЙ ПОИСК ---
        // Ищем ID, которого точно нет (чтобы алгоритм прошел весь массив)
        auto start = high_resolution_clock::now();
        Search::linear_Search_By_Id(tasks, n, -999);
        auto end = high_resolution_clock::now();
        double linearTime = duration<double, milli>(end - start).count();

        // --- 2. БИНАРНЫЙ ПОИСК ---
        // Сначала сортируем массив по ID (обязательное условие для бинарного поиска)
        Task* sortedTasks = new Task[n];
        copy(tasks, tasks + n, sortedTasks);
        sort(sortedTasks, sortedTasks + n, [](const Task& a, const Task& b) {
            return a.id < b.id;
        });

        start = high_resolution_clock::now();
        Search::binary_Search_By_Id(sortedTasks, n, -999); // Ищем тот же отсутствующий ID
        end = high_resolution_clock::now();
        double binaryTime = duration<double, milli>(end - start).count();

        // --- 3. BST (Вставка всех + извлечение топ-10) ---
        start = high_resolution_clock::now();
        BST tree;
        for (int i = 0; i < n; ++i) {
            tree.insert(tasks[i]);
        }
        int topCount;
        Task* treeTop = tree.extractTopN(10, topCount);
        end = high_resolution_clock::now();
        double bstTime = duration<double, milli>(end - start).count();

        // --- 4. ПОЛНАЯ СОРТИРОВКА (для сравнения с BST) ---
        // Используем встроенную сортировку (т.к. сортировки 4-го участника пока нет)
        start = high_resolution_clock::now();
        Task* copyTasks = new Task[n];
        copy(tasks, tasks + n, copyTasks);
        sort(copyTasks, copyTasks + n, [](const Task& a, const Task& b) {
            if (a.priority != b.priority) return a.priority < b.priority;
            if (a.deadline != b.deadline) return a.deadline < b.deadline;
            return a.id < b.id;
        });

        // Берем первые 10
        const int topSize = min(10, n);
        Task* top10 = new Task[topSize];
        copy(copyTasks, copyTasks + topSize, top10);
        end = high_resolution_clock::now();
        double sortTime = duration<double, milli>(end - start).count();

        delete[] top10;
        delete[] copyTasks;
        delete[] treeTop;
        delete[] sortedTasks;
        delete[] tasks;

        // Вывод результатов для текущего размера
        cout << n << "\t" << linearTime << "\t\t" << binaryTime << "\t\t"
             << bstTime << "\t" << sortTime << "\n";
    }

    return 0;
}

/*g++ -O2 -Iinclude src/Search.cpp src/BST.cpp main.cpp -o bench_app*/
/*./bench_app.exe*/