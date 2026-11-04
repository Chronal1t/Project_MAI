from src.models import Task


def dummy_sort_by_key(tasks: list[Task], key) -> list[Task]:
    """Вспомогательная сортировка вставками для тестов бинарного поиска."""
    arr = list(tasks)
    for i in range(1, len(arr)):
        cur = arr[i]
        j = i - 1
        while j >= 0 and key(arr[j]) > key(cur):
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = cur
    return arr