#pragma once
#include <mutex>
#include <atomic>

// Ортогональная стратегия: управление потоками

// 1. Однопоточная версия (без синхронизации)
template <typename T>
struct SingleThreaded {
    struct DummyLock {}; // Заглушка для совместимости с интерфейсом
    static void Lock(DummyLock&) {} // Пустые методы
    static void Unlock(DummyLock&) {}
};

// 2. Многопоточная версия с std::mutex (стандартная)
template <typename T>
struct MultiThreaded {
    using Lock = std::mutex;
    static void Lock(Lock& mtx) { mtx.lock(); }
    static void Unlock(Lock& mtx) { mtx.unlock(); }
};

// 3. Многопоточная версия с атомарным флагом (оптимизированная)
template <typename T>
struct AtomicThreaded {
    using Lock = std::atomic_flag;
    static void Lock(Lock& flag) {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // Spin until lock is acquired
        }
    }
    static void Unlock(Lock& flag) {
        flag.clear(std::memory_order_release);
    }
};
