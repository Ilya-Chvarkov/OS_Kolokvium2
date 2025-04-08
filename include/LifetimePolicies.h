#pragma once

// Удаление при завершении программы (стандартное)
template <typename T>
struct DefaultLifetime {
    static void ScheduleDestruction(T*, void (*pFun)()) {
        std::atexit(pFun);
    }
};

// Не удалять никогда (например, для статических объектов)
template <typename T>
struct NoDestroy {
    static void ScheduleDestruction(T*, void (*)()) {}
};
