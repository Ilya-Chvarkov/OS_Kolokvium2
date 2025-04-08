#pragma once
#include "CreationPolicies.h"
#include "LifetimePolicies.h"
#include "ThreadingPolicies.h"

template <
    typename T,
    template <typename> class CreationPolicy = CreateUsingNew,
    template <typename> class ThreadingPolicy = MultiThreaded,
    template <typename> class LifetimePolicy = DefaultLifetime
>
class Singleton {
public:
    static T& Instance() {
        if (!pInstance_) {
            typename ThreadingPolicy<T>::Lock guard;
            ThreadingPolicy<T>::Lock(guard);
            if (!pInstance_) {
                pInstance_ = CreationPolicy<T>::Create();
                LifetimePolicy<T>::ScheduleDestruction(pInstance_, &DestroySingleton);
            }
            ThreadingPolicy<T>::Unlock(guard);
        }
        return *pInstance_;
    }

private:
    static void DestroySingleton() {
        CreationPolicy<T>::Destroy(pInstance_);
        pInstance_ = nullptr;
    }

    Singleton() = delete;
    ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T* pInstance_;
};

template <typename T, typename C, typename L, typename M>
T* Singleton<T, C, L, M>::pInstance_ = nullptr;
