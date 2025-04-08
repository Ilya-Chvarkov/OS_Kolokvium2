// Singleton.h - Реализация с ортогональными стратегиями
#pragma once

#include <mutex>
#include <atomic>
#include <cstdlib>

// ======== Стратегии создания ========
template <typename T>
struct CreateUsingNew {
    static T* Create() { return new T(); }
    static void Destroy(T* p) { delete p; }
};

template <typename T>
struct CreateStatic {
    static T* Create() {
        static T instance;
        return &instance;
    }
    static void Destroy(T*) {} // Ничего не делаем для static
};

// ======== Стратегии времени жизни ========
template <typename T>
class DefaultLifetime {
public:
    static void ScheduleDestruction(void (*func)()) {
        std::atexit(func);
    }
    static bool IsDestroyed() { return false; }
};

template <typename T>
class PhoenixSingleton {
public:
    static void ScheduleDestruction(void (*func)()) {
        std::atexit(func);
    }
    static void OnDeadReference() { destroyed_ = true; }
    static bool IsDestroyed() { return destroyed_; }
    
private:
    static bool destroyed_;
};

template <typename T> bool PhoenixSingleton<T>::destroyed_ = false;

// ======== Стратегии потокобезопасности ========
class SingleThreaded {
public:
    struct Lock { Lock() {} ~Lock() {} };
    using AtomicInt = int;
};

class MultiThreaded {
public:
    struct Lock {
        Lock() { mtx_.lock(); }
        ~Lock() { mtx_.unlock(); }
    private:
        static std::mutex mtx_;
    };
    using AtomicInt = std::atomic<int>;
};

template <typename T> std::mutex MultiThreaded::mtx_;

// ======== Ядро Singleton ========
template <typename T,
          template <typename> class CreationPolicy = CreateUsingNew,
          template <typename> class LifetimePolicy = DefaultLifetime,
          template <typename> class ThreadingModel = MultiThreaded>
class Singleton {
public:
    static T& Instance() {
        if (!instance_) {
            typename ThreadingModel<T>::Lock guard;
            if (!instance_) {
                if (LifetimePolicy<T>::IsDestroyed()) {
                    LifetimePolicy<T>::OnDeadReference();
                    destroyed_ = false;
                }
                instance_ = CreationPolicy<T>::Create();
                LifetimePolicy<T>::ScheduleDestruction(&DestroySingleton);
            }
        }
        return *instance_;
    }

private:
    static void DestroySingleton() {
        CreationPolicy<T>::Destroy(instance_);
        instance_ = nullptr;
        destroyed_ = true;
    }

    static T* instance_;
    static bool destroyed_;

    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

template <typename T, template <typename> class CP, template <typename> class LP, template <typename> class TM>
T* Singleton<T, CP, LP, TM>::instance_ = nullptr;

template <typename T, template <typename> class CP, template <typename> class LP, template <typename> class TM>
bool Singleton<T, CP, LP, TM>::destroyed_ = false;
