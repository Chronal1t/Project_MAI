#include <iostream>
#include <cassert>
#include <vector>
#include "Task.h"
#include "Search.h"
#include "BST.h"

using namespace std;

// --- ТЕСТЫ ПОИСКА ---

void test_linear_search() {
    vector<Task> tasks = {
        {1, "  Buy MILK  ", 3, "2026-01-01", "todo", 1, 1},
        {2, "Fix car", 2, "2026-01-02", "todo", 1, 1},
        {3, "milk the cow", 1, "2026-01-03", "todo", 2, 2}
    };
    
    // Ищем "milk" (должен найти 1-ю и 3-ю задачу, регистр и пробелы не важны)
    vector<int> res = Search::linear_Search_By_Name(tasks, "milk");
    assert(res.size() == 2);
    assert(res[0] == 0); // Первая задача
    assert(res[1] == 2); // Третья задача

    // Ищем ID=2 (должен вернуть индекс 1)
    int id_idx = Search::linear_Search_By_Id(tasks, 2);
    assert(id_idx == 1);

    // Ищем несуществующий ID
    int no_id_idx = Search::linear_Search_By_Id(tasks, 99);
    assert(no_id_idx == -1);

    cout << "Test Linear Search: PASSED" << endl;
}

void test_binary_search() {
    // ВАЖНО: Для бинарного поиска список должен быть отсортирован по ID!
    vector<Task> sortedTasks = {
        {1, "Task A", 3, "2026-01-01", "todo", 1, 1},
        {2, "Task B", 2, "2026-01-02", "todo", 1, 1},
        {3, "Task C", 1, "2026-01-03", "todo", 2, 2},
        {4, "Task D", 5, "2026-01-04", "todo", 2, 2}
    };

    // Ищем существующий ID=3 (индекс 2)
    int idx = Search::binary_Search_By_Id(sortedTasks, 3);
    assert(idx == 2);

    // Ищем несуществующий ID=5
    int no_idx = Search::binary_Search_By_Id(sortedTasks, 5);
    assert(no_idx == -1);

    cout << "Test Binary Search: PASSED" << endl;
}

// --- ТЕСТЫ BST ---

void test_bst() {
    BST tree;
    
    // Вставляем в разном порядке
    tree.insert({1, "Low", 3, "2026-03-01", "todo", 1, 1});
    tree.insert({2, "High", 1, "2026-01-01", "todo", 1, 1});
    tree.insert({3, "Medium", 2, "2026-02-01", "todo", 1, 1});

    // Достаем топ-2
    vector<Task> top2 = tree.extractTopN(2);
    assert(top2.size() == 2);
    
    // Первым должен идти High (приоритет 1), вторым Medium (приоритет 2)
    assert(top2[0].id == 2);
    assert(top2[1].id == 3);

    // Достаем больше, чем есть (должны получить все 3)
    vector<Task> top10 = tree.extractTopN(10);
    assert(top10.size() == 3);

    // Проверка пустого дерева
    BST emptyTree;
    vector<Task> emptyRes = emptyTree.extractTopN(5);
    assert(emptyRes.size() == 0);

    cout << "Test BST: PASSED" << endl;
}

int main() {
    cout << "--- Running all tests ---" << endl;
    
    test_linear_search();
    test_binary_search();
    test_bst();
    
    cout << "--- All tests passed! ---" << endl;
    return 0;
}