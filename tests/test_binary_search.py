from datetime import date
from src.models import Task
from src.search import binary_search_by_id, binary_search_by_title_exact
from tests.helpers import dummy_sort_by_key


def test_binary_search_empty():
    assert binary_search_by_id([], 1) is None


def test_binary_search_by_id():
    # Создаем список вразброс
    tasks = [
        Task(5, "E", 1, date(2026, 1, 1)),
        Task(2, "B", 1, date(2026, 1, 1)),
        Task(9, "I", 1, date(2026, 1, 1)),
        Task(1, "A", 1, date(2026, 1, 1)),
        Task(7, "G", 1, date(2026, 1, 1)),
    ]
    # Сортируем с помощью вспомогательной функции
    sorted_tasks = dummy_sort_by_key(tasks, key=lambda t: t.id)
    
    # Проверяем поиск всех элементов и одного отсутствующего
    assert binary_search_by_id(sorted_tasks, 1) == 0
    assert binary_search_by_id(sorted_tasks, 2) == 1
    assert binary_search_by_id(sorted_tasks, 5) == 2
    assert binary_search_by_id(sorted_tasks, 7) == 3
    assert binary_search_by_id(sorted_tasks, 9) == 4
    assert binary_search_by_id(sorted_tasks, 3) is None  # нет такого


def test_binary_search_by_title_exact():
    tasks = [
        Task(1, "Apple", 1, date(2026, 1, 1)),
        Task(2, "Banana", 1, date(2026, 1, 1)),
        Task(3, "Cherry", 1, date(2026, 1, 1)),
        Task(4, "Date", 1, date(2026, 1, 1)),
    ]
    # Сортируем по названию (учитывая нормализацию)
    sorted_tasks = dummy_sort_by_key(tasks, key=lambda t: t.title.lower().strip())
    
    # Ищем точное совпадение (проверяем и регистронезависимость)
    assert binary_search_by_title_exact(sorted_tasks, "Banana") == 1
    assert binary_search_by_title_exact(sorted_tasks, "cherry") == 2
    assert binary_search_by_title_exact(sorted_tasks, "Apple") == 0
    
    # Подстрока НЕ должна находиться бинарным поиском!
    assert binary_search_by_title_exact(sorted_tasks, "App") is None