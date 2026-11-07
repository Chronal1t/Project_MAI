#pragma once
#include <vector>
#include "Task.h"

using namespace std;
// Узел дерева
struct BSTNode {
    Task task;
    BSTNode* left;
    BSTNode* right;
    
    // Конструктор узла 
    BSTNode(const Task& t) : task(t), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root; // Указатель на корень дерева
    
    // Приватные рекурсивные методы
    void insert(BSTNode*& node, const Task& task);
    void fillTopN(BSTNode* node, int n, vector<Task>& result);
    void clear(BSTNode* node); // Для очистки памяти

public:
    BST();  // Конструктор
    ~BST(); // Деструктор (вызывается автоматически при удалении дерева)

    void insert(const Task& task);
    vector<Task> extractTopN(int n);
};