# OS_Kolokvium2
# Modern C++ Singleton with Orthogonal Policies

Реализация шаблона Singleton с ортогональными стратегиями, вдохновлённая книгой А. Александреску "Modern C++ Design".

## Особенности
- Поддержка различных стратегий:
  - **Создание**: `CreateUsingNew`, `CreateStatic`
  - **Потоки**: `SingleThreaded`, `MultiThreaded`, `AtomicThreaded`
  - **Время жизни**: `DefaultLifetime`, `NoDestroy`
- Потокобезопасность через Double-Checked Locking
- Конфигурируется через `config.h`

## Использование
```cpp
#include "Singleton.h"

class MyClass { /* ... */ };

// Стандартное использование
auto& instance = Singleton<MyClass>::Instance();

// Кастомные политики
auto& staticObj = Singleton<MyClass, CreateStatic, SingleThreaded>::Instance();
