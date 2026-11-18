# Архитектура

Слои (сверху вниз):
- Web UI (frontend/) — HTML/JS, общается с API по HTTP/JSON.
- API (src/router, src/http, обработчики) — маршрутизация, auth-middleware, валидация, ошибки.
- Services (src/services/*) — бизнес-логика: TaskService, AuthService, ...
- Domain (src/models.h) — Task, User, Team, TaskGraph.
- Algorithms (src/algorithms/*) — свои поиск/сортировки/BST/DFS/топосорт.
- Storage (src/db, src/*Repository) — SQLite + CSV/JSON loaders.

Схема БД: (см. ниже — вставим на Этапе 4)

Поток запроса:
HTTP → Router → Middleware(requireAuth) → Controller → Service → Repository → SQLite