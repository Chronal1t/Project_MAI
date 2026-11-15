#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "Task.h"
#include "Search.h"
#include "BST.h"

using namespace std;
using namespace std::chrono;

// Функция для генерации случайных задач
vector<Task> generateRandomTasks(int n) {
    vector<Task> tasks;
    tasks.reserve(n);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> idDist(1, 1000000);
    uniform_int_distribution<> prioDist(1, 5);
    
    for (int i = 0; i < n; ++i) {
        Task t;
        t.id = idDist(gen);
        t.name = "Task " + to_string(i);
        t.priority = prioDist(gen);
        t.deadline = "2026-01-01";
        t.status = "todo";
        t.id_team = 1;
        t.id_human = 1;
        tasks.push_back(t);
    }
    return tasks;
}

int main() {
    vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000};
    
    cout << "Size\tLinear(ms)\tBinary(ms)\tBST(ms)\tFullSort(ms)\n";
    cout << "------------------------------------------------------------------------\n";

    for (int n : sizes) {
        auto tasks = generateRandomTasks(n);
        
        // --- 1. ЛИНЕЙНЫЙ ПОИСК ---
        // Ищем ID, которого точно нет (чтобы алгоритм прошел весь массив)
        auto start = high_resolution_clock::now();
        Search::linear_Search_By_Id(tasks, -999);
        auto end = high_resolution_clock::now();
        double linearTime = duration<double, milli>(end - start).count();

        // --- 2. БИНАРНЫЙ ПОИСК ---
        // Сначала сортируем массив по ID (обязательное условие для бинарного поиска)
        auto sortedTasks = tasks;
        sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
            return a.id < b.id;
        });
        
        start = high_resolution_clock::now();
        Search::binary_Search_By_Id(sortedTasks, -999); // Ищем тот же отсутствующий ID
        end = high_resolution_clock::now();
        double binaryTime = duration<double, milli>(end - start).count();

        // --- 3. BST (Вставка всех + извлечение топ-10) ---
        start = high_resolution_clock::now();
        BST tree;
        for (const auto& t : tasks) {
            tree.insert(t);
        }
        tree.extractTopN(10);
        end = high_resolution_clock::now();
        double bstTime = duration<double, milli>(end - start).count();

        // --- 4. ПОЛНАЯ СОРТИРОВКА (для сравнения с BST) ---
        // Используем встроенную сортировку (т.к. сортировки 4-го участника пока нет)
        start = high_resolution_clock::now();
        auto copyTasks = tasks;
        sort(copyTasks.begin(), copyTasks.end(), [](const Task& a, const Task& b) {
            if (a.priority != b.priority) return a.priority < b.priority;
            if (a.deadline != b.deadline) return a.deadline < b.deadline;
            return a.id < b.id;
        });
        // Берем первые 10
        vector<Task> top10(copyTasks.begin(), copyTasks.begin() + min(10, n));
        end = high_resolution_clock::now();
        double sortTime = duration<double, milli>(end - start).count();

        // Вывод результатов для текущего размера
        cout << n << "\t" << linearTime << "\t\t" << binaryTime << "\t\t" 
             << bstTime << "\t" << sortTime << "\n";
    }

    return 0;
}

/*g++ -O2 -Iinclude src/Search.cpp src/BST.cpp main.cpp -o bench_app*/
/*./bench_app.exe*/