cmake_minimum_required(VERSION 3.28)
project(Pong)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pong main.cpp Bat.cpp)

#add_executable(Pong ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Pong sfml-system sfml-window sfml-graphics sfml-audio sfml-network)