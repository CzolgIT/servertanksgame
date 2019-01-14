cmake_minimum_required(VERSION 3.5)
project(servertanksgame)

# use cmake/FindSDL2*.cmake
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# enable C++11
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -ggdb ${CMAKE_CXX_FLAGS}")


find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")
add_executable(servertanksgame ${SOURCES} include/Models/Wall.h src/Models/Wall.cpp)

# use cmake/FindSDL2*.cmake
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


include_directories(
        "include/*/*"
        "include/*"
        "include/"
        ${SDL2_INCLUDE_DIR}
        ${SDL2_NET_INCLUDE_DIR}
)

target_link_libraries(servertanksgame
        ${SDL2_LIBRARY}
        ${SDL2_NET_LIBRARY}
        )