from dataclasses import dataclass, field
from datetime import date


@dataclass
class Task:
    id: int
    title: str
    priority: int          # 1 = высший приоритет
    deadline: date
    status: str = "todo"   # "todo" / "done"
    tags: list[str] = field(default_factory=list)
    dependencies: list[int] = field(default_factory=list)