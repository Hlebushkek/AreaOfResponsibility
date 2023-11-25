cmake_minimum_required(VERSION 3.9)
project(aor)

enable_language(C)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "source/*.cpp" "include/*.hpp")
file(GLOB MAIN_SRC "source/main.cpp" "source/main_tests.cpp" "source/main_20tests.cpp" "source/main_genetic_tests.cpp")
list(REMOVE_ITEM SOURCES ${MAIN_SRC})
include_directories(include)

add_executable(${PROJECT_NAME} "source/main.cpp" ${SOURCES})
add_executable(${PROJECT_NAME}_tests "source/main_tests.cpp" ${SOURCES})
add_executable(${PROJECT_NAME}_20tests "source/main_20tests.cpp" ${SOURCES})
add_executable(${PROJECT_NAME}_genetic_tests "source/main_genetic_tests.cpp" ${SOURCES})

add_subdirectory(SFML)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME}_tests sfml-graphics)
target_link_libraries(${PROJECT_NAME}_20tests sfml-graphics)
target_link_libraries(${PROJECT_NAME}_genetic_tests sfml-graphics)