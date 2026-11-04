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



"Бинарный поиск по ID"

def binary_search_by_id(sorted_task :list[Task], target_id):
    left=0 #правый указатель 
    right=len(sorted_task )-1 # левый указатель 

    while left<=right:
        mid=(left+right)//2 # находм середину
        if sorted_task[mid].id==target_id:
            return mid # нашли, возвращаем индекс
        elif sorted_task[mid].id<=target_id:
            left=mid+1 #  сдвигаем правее
        else:
            right=mid-1 # сдвигаем левее
    return None

"Бинарный поиск по title"
def binary_search_by_title_exact(sorted_task : list[Task], title):
    
    target=normalize(title)

    left=0 #правый указатель 
    right=len(sorted_task )-1 # левый указатель 
    
    while left<=right:
        mid=(left+right)//2 # находм середину
        cur = normalize(sorted_task[mid].title) # приводим к нормальному виду
        if cur==target:
            return mid  # нашли, возвращаем индекс
        elif cur<=target:
            left=mid+1 #  сдвигаем правее
        else:
            right=mid-1 # сдвигаем левее
    return None