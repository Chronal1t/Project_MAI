from datetime import date
from src.models import Task
from src.BST import BST

def test_bst_empty():
    tree = BST()
    assert tree.extract_top_n(5) == []

def test_bst_insert_and_extract():
    tree = BST()
    # Создаем задачи с разными приоритетами (1 - высший)
    # Дедлайны тоже делаем разными, чтобы они не влияли на сортировку приоритетов
    t1 = Task(1, "Low priority", 3, date(2026, 3, 1))
    t2 = Task(2, "High priority", 1, date(2026, 1, 1))
    t3 = Task(3, "Medium priority", 2, date(2026, 2, 1))
    
    tree.insert(t1)
    tree.insert(t2)
    tree.insert(t3)
    
    # Просим топ-2. Должны получить t2 (приоритет 1) и t3 (приоритет 2)
    top_2 = tree.extract_top_n(2)
    
    assert len(top_2) == 2
    assert top_2[0].id == 2  # Самый высокий приоритет
    assert top_2[1].id == 3  # Второй по высоте

def test_bst_extract_more_than_exists():
    tree = BST()
    tree.insert(Task(1, "Only task", 1, date(2026, 1, 1)))
    
    # Просим 10, а есть только 1
    top_10 = tree.extract_top_n(10)
    assert len(top_10) == 1