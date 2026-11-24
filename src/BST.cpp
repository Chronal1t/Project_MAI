


#include "BST.h"
#include <tuple>

using namespace std;

// Конструктор
BST::BST() : root(nullptr) {}

// Деструктор (будет вызван автоматически, когда дерево больше не нужно)
BST::~BST() {
    clear(root);
}

// Вспомогательная функция для очистки памяти
void BST::clear(BSTNode* node) {
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node; // Удаляем узел из памяти
    }
}

// Функция для создания ключа (сравнение по приоритету, затем по дедлайну, затем по ID)
auto getKey(const Task& t)
{
    return make_tuple(t.priority, t.deadline, t.id);
}

// Публичный метод вставки (начинает с корня)
void BST::insert(const Task& task)
{
    insert(root, task);
}

// Рекурсивная вставка
void BST::insert(BSTNode*& node, const Task& task)
{
    if (node == nullptr)
    {
        // Нашли пустое место — создаем новый узел
        node = new BSTNode(task);
        return;
    }

    if (getKey(task) < getKey(node->task))
    {
        insert(node->left, task); // Идем влево
    }
    else
    {
        insert(node->right, task); // Идем вправо
    }
}

// Публичный метод извлечения топ-N
Task* BST::extractTopN(int n, int& count)
{
    count = 0;
    if (n <= 0 || root == nullptr)
    {
        return nullptr;
    }

    Task* result = new Task[n];
    fillTopN(root, n, result, count);
    return result;
}

// Рекурсивный обход (Лево -> Узел -> Право)
void BST::fillTopN(BSTNode* node, int n, Task* result, int& count)
{
    if (node == nullptr || count >= n)
    {
        return;
    }

    // 1. Идем влево (там самые высокие приоритеты)
    fillTopN(node->left, n, result, count);

    // 2. Берем текущий узел (если еще не набрали N)
    if (count < n)
    {
        result[count++] = node->task;
    }

    // 3. Идем вправо
    fillTopN(node->right, n, result, count);
}