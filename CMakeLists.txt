cmake_minimum_required(VERSION 3.9)
project(aor)

enable_language(C)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "source/*.cpp" "include/*.hpp")
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(SFML)
target_link_libraries(${PROJECT_NAME} sfml-graphics)