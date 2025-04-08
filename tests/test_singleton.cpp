#include "Singleton.h"
#include "config.h"
#include <thread>
#include <vector>
#include <cassert>

// Тестовый класс для демонстрации
class TestService {
public:
    void increment() { counter++; }
    int get() const { return counter; }
private:
    int counter = 0;
};

// 1. Тест базовой функциональности
void test_basic_functionality() {
    auto& instance1 = Singleton<TestService>::Instance();
    auto& instance2 = Singleton<TestService>::Instance();
    assert(&instance1 == &instance2); // Проверка, что это один и тот же объект
    instance1.increment();
    assert(instance2.get() == 1);
}

// 2. Тест потокобезопасности
void test_thread_safety() {
    std::vector<std::thread> threads;
    constexpr int kThreadCount = 100;

    for (int i = 0; i < kThreadCount; ++i) {
        threads.emplace_back([]() {
            auto& service = Singleton<TestService>::Instance();
            service.increment();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(Singleton<TestService>::Instance().get() == kThreadCount + 1); // +1 из предыдущего теста
}

// 3. Тест политик
void test_policies() {
    struct TestStatic {};
    auto& staticInstance = Singleton<TestStatic, CreateStatic>::Instance();
    // Проверка, что объект создан через placement new
}

int main() {
    test_basic_functionality();
    test_thread_safety();
    test_policies();
    return 0;
}
