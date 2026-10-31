from src.models import Task
from src.untils import normalize



"""Поиск подстроки в названии, регистронезависимый. O(n * m)."""
def linear_search_by_title(tasks: list[Task], word: str) -> list[int]:

    needle = normalize(word)
    result = []
    for i, t in enumerate(tasks):
        if needle in normalize(t.title):
            result.append(i)
    return result # возвращает индексы задачи в списке

"""Линейный поиск по ID. O(n). Возвращает индекс или None."""
def linear_search_by_id(tasks: list[Task], target_id: int) -> int | None:

    for i, t in enumerate(tasks):
        if t.id == target_id:
            return i
    return None


"""Поиск по статусу. O(n)."""
def linear_search_by_status(tasks: list[Task], status: str) -> list[int]:

    for i, t in enumerate(tasks):
        if t.status == status:
            return [i]
    return []
    