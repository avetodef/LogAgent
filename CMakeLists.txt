cmake_minimum_required(VERSION 3.10)
project(LogAgent VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Автоматический поиск исходных файлов (только .cpp)
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/Aggregation/*.cpp"
        "src/Criteria/*.cpp"
        "src/Repository/*.cpp"
        "src/Model/*.cpp"
        )

# Автоматический поиск заголовочных файлов (только .hpp)
file(GLOB_RECURSE HEADERS
        "src/*.hpp"
        "src/Aggregation/*.hpp"
        "src/Command/*.hpp"
        "src/Criteria/*.hpp"
        "src/Repository/*.hpp"
        "src/Model/*.hpp"
        )

# Проверка наличия исходных файлов
if(NOT SOURCES)
    message(FATAL_ERROR "No source files (*.cpp) found in project directories")
endif()

# Создание исполняемого файла
add_executable(LogAgent ${SOURCES} ${HEADERS})

# Установка путей для заголовочных файлов
target_include_directories(LogAgent PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# Подключение зависимостей (если нужны)
find_package(Threads REQUIRED)
target_link_libraries(LogAgent PRIVATE Threads::Threads)

# Опционально: вывод информации о найденных файлах
message(STATUS "Found ${SOURCES} source files")
message(STATUS "Found ${HEADERS} header files")