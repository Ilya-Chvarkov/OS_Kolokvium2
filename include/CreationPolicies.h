#pragma once

// Стратегия: создание через new
template <typename T>
struct CreateUsingNew {
    static T* Create() {
        return new T();
    }
    static void Destroy(T* p) {
        delete p;
    }
};

// Стратегия: создание через статический буфер (например, для embedded)
template <typename T>
struct CreateStatic {
    static T* Create() {
        static char buffer[sizeof(T)];
        return new (buffer) T(); // placement new
    }
    static void Destroy(T* p) {
        p->~T();
    }
};
