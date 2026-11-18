# API контракт (v0.1)

Base URL: http://localhost:8080
Все ответы — JSON, кроме `/` и `/style.css` (статика).
Ошибки: `{ "error": { "code": "...", "message": "..." } }`

## Auth
POST /api/auth/register  { username, password, teamName }
  → 201 { token, user: { id, username, teamId } }
POST /api/auth/login     { username, password }
  → 200 { token, user: { id, username, teamId } }
POST /api/auth/logout    (Authorization: Bearer <token>) → 204
GET  /api/auth/me        (Authorization: Bearer <token>)
  → 200 { id, username, teamId }

## Tasks (все — в рамках команды текущего юзера)
GET  /api/tasks?q=&status=&priority=&sort=&order=&topN=&topMode=
  → 200 [ Task, ... ]
POST /api/tasks  { name, priority, deadline, tags?, dependsOn? }
  → 201 Task
GET  /api/tasks/:id → 200 Task | 404
PUT  /api/tasks/:id { name?, priority?, deadline? } → 200 Task
DELETE /api/tasks/:id → 204 | 404
PATCH /api/tasks/:id/complete → 200 Task | 409 (есть незавершённые зависимости)
POST /api/tasks/import?format=csv|json  (raw body файла) → 200 { imported, errors: [...] }
GET  /api/tasks/recommended → 200 [ Task, ... ] (топопорядок)

## Dependencies
POST   /api/dependencies { fromId, toId }   (from зависит от to)
DELETE /api/dependencies { fromId, toId }
GET    /api/dependencies/graph → { nodes: [...], edges: [{from,to}] }
GET    /api/dependencies/cycles → { hasCycle, cycle? }

## Stats
GET /api/stats → { total, done, undone, byPriority: { "1": n, ... } }

## Task (структура по ТЗ + расширения)
{
  "id": 1,
  "name": "Купить молоко",
  "priority": 3,
  "status": false,
  "deadline": "2026-11-10",
  "tags": ["home"],
  "dependsOn": [2, 3],
  "teamId": 1,
  "ownerId": 5
}