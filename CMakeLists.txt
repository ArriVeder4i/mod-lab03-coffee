cmake_minimum_required(VERSION 3.10)
project(VendingMachine)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем пути для заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/include)

# Создаём исполняемый файл для основной программы
add_executable(mod-lab03-coffee.test test/main.cpp)
target_link_libraries(mod-lab03-coffee.test PRIVATE your_library)
add_test(NAME mod-lab03-coffee.test COMMAND mod-lab03-coffee.test)

add_executable(vending_machine
    src/main.cpp
    src/Automata.cpp
)

# Настройка Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Устанавливаем опции для Google Test перед его сборкой
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включаем тестирование
enable_testing()

# Создаём исполняемый файл для тестов
add_executable(mod-lab03-coffee.test
    test/tests.cpp
    src/Automata.cpp
)

# Линкуем тесты с GTest
target_link_libraries(mod-lab03-coffee.test GTest::gtest_main)

# Добавляем тесты в систему
add_test(NAME AutomataTests COMMAND mod-lab03-coffee.test)
