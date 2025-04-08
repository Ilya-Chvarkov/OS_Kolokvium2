cmake_minimum_required(VERSION 3.10)
project(ModernCppSingleton LANGUAGES CXX)

# Настройка стандарта C++ (требуется C++17 из-за std::mutex и других фич)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции проекта
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DEMO "Build demo application" ON)

# Основная библиотека (header-only)
add_library(Singleton INTERFACE)
target_include_directories(Singleton INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Демо-приложение
if(BUILD_DEMO)
    add_executable(demo src/demo.cpp)
    target_link_libraries(demo Singleton)
endif()

# Тесты (используем Google Test)
if(BUILD_TESTS)
    enable_testing()

    # Поиск GTest
    find_package(GTest REQUIRED)
    include(GoogleTest)

    # Исполняемый файл для тестов
    add_executable(singleton_tests tests/test_singleton.cpp)
    target_link_libraries(singleton_tests Singleton GTest::GTest GTest::Main)

    # Добавляем тесты в CTest
    gtest_discover_tests(singleton_tests)
endif()

# Установка (опционально)
install(DIRECTORY include/ DESTINATION include)
install(TARGETS Singleton EXPORT SingletonConfig)
install(EXPORT SingletonConfig DESTINATION lib/cmake/Singleton)
