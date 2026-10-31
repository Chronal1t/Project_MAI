def normalize(s: str) -> str:
    """Нижний регистр + обрезка пробелов. Единое правило для поиска и сортировки."""
    return s.lower().strip()
