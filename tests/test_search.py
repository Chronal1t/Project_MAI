from datetime import date
from src.models import Task
from src.search import linear_search_by_title, linear_search_by_id, linear_search_by_status


def test_linear_empty():
    assert linear_search_by_title([], "x") == []
    assert linear_search_by_id([], 1) is None


def test_linear_no_match():
    tasks = [Task(1, "Buy milk", 3, date(2026, 1, 1))]
    assert linear_search_by_title(tasks, "bread") == []
    assert linear_search_by_id(tasks, 99) is None


def test_linear_case_insensitive():
    tasks = [Task(1, "Buy MILK", 3, date(2026, 1, 1))]
    assert linear_search_by_title(tasks, "milk") == [0]
    assert linear_search_by_title(tasks, "MILK") == [0]


def test_linear_substring():
    tasks = [
        Task(1, "Buy milk", 3, date(2026, 1, 1)),
        Task(2, "Milk the cow", 2, date(2026, 1, 2)),
        Task(3, "Bread", 1, date(2026, 1, 3))
    ]
    assert linear_search_by_title(tasks, "milk") == [0, 1]


def test_linear_search_by_status():
    tasks = [
        Task(1, "Buy milk", 3, date(2026, 1, 1), status="todo"),
        Task(2, "Fix bug", 2, date(2026, 1, 2), status="done")
    ]
    assert linear_search_by_status(tasks, "todo") == [0]
    assert linear_search_by_status(tasks, "done") == [1]