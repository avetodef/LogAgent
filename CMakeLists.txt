cmake_minimum_required(VERSION 3.10)
project(LogAgent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
        "src/*.cpp"
        "src/*.hpp"
        "src/Aggregation/*.cpp"
        "src/Command/*.cpp"
        "src/Criteria/*.cpp"
        "src/Repository/*.cpp"
        "src/Model/*.cpp"
        )
list(FILTER SOURCES EXCLUDE REGEX "CMakeFiles/.*|CompilerIdCXX.cpp")
add_executable(ComputerClub ${SOURCES} src/main.cpp)

target_include_directories(ComputerClub PRIVATE
        src
        src/Aggregation
        src/Command
        src/Criteria
        src/Repository
        src/Model
        )