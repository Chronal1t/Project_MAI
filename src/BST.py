from src.models import Task

class BSTNode:
    def __init__(self, task : Task):
        self.task = task
        self.left = None
        self.right = None
        


class BST :
    def __init__(self):
        self.root = None


    def _get_key(self, task: Task):
        "Минус перед приоритетом нужен чтобы высший приоритет считался меньше и уходил влево"
        return (task.priority, task.deadline, task.id)
        


    def insert(self, task: Task):
        self.root = self._insert(self.root, task)

    def _insert(self, node: BSTNode, task: Task):
        if node is None:
            return BSTNode(task)
        
        if self._get_key(task) < self._get_key(node.task):
            node.left = self._insert(node.left, task)
        else:
            node.right = self._insert(node.right, task)
        return node

    def  extract_top_n(self, n :int) ->list[Task]:
        result=[]
        self._fill_top_n(self.root, n, result)
        return result

    def _fill_top_n(self, node, n, result):
        if node is None or len(result) >= n:
            return
        
        # 1. Идем влево (туда, где самые высокие приоритеты)
        self._fill_top_n(node.left, n, result)
        
        # 2. Берем текущий узел (если еще не набрали N)
        if len(result) < n:
            result.append(node.task)
            
        # 3. Идем вправо
        self._fill_top_n(node.right, n, result)   
            
