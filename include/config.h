#pragma once

// Файл для предварительной конфигурации политик по умолчанию

#ifndef SINGLETON_DEFAULT_CREATION
#define SINGLETON_DEFAULT_CREATION CreateUsingNew
#endif

#ifndef SINGLETON_DEFAULT_THREADING
#define SINGLETON_DEFAULT_THREADING MultiThreaded
#endif

#ifndef SINGLETON_DEFAULT_LIFETIME
#define SINGLETON_DEFAULT_LIFETIME DefaultLifetime
#endif

// Упрощённый алиас для стандартного использования
template <typename T>
using DefaultSingleton = Singleton<
    T,
    SINGLETON_DEFAULT_CREATION,
    SINGLETON_DEFAULT_THREADING,
    SINGLETON_DEFAULT_LIFETIME
>;
