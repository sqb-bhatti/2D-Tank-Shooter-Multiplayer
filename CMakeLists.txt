cmake_minimum_required(VERSION 3.28)
project(MarioClone)

set(CMAKE_CXX_STANDARD 20)

add_executable(MarioClone main.cpp
        src/Server.cpp
        src/Server.h
        src/settings.h
        src/Client.cpp
        src/Client.h
        src/game/Player.cpp
        src/game/Player.h
        src/game/World.cpp
        src/game/World.h
        src/game/Projectile.cpp
        src/game/Projectile.h)

include_directories(/usr/local/include)


find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(MarioClone sfml-system sfml-window sfml-graphics sfml-audio sfml-network)