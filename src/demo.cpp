#include "../include/Singleton.h"
#include <iostream>

class Logger {
public:
    void Log(const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    }
};

int main() {
    Singleton<Logger>::Instance().Log("Hello, Singleton!");
    return 0;
}
