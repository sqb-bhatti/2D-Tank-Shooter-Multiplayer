cmake_minimum_required(VERSION 3.28)
project(TWL)

set(CMAKE_CXX_STANDARD 17)

add_executable(TWL main.cpp
        TextureHolder.cpp
        TextureHolder.h
        Engine.cpp
        Engine.h
        Input.cpp
        Update.cpp
        Draw.cpp
        PlayableCharacter.cpp
        PlayableCharacter.h
        Thomas.cpp
        Thomas.h
        Bob.cpp
        Bob.h
        LevelManager.cpp
        LevelManager.h
        LoadLevel.cpp
        DetectCollisions.cpp
        SoundManager.cpp
        SoundManager.h
        PopulateEmitters.cpp)

include_directories(/usr/local/include)


find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(TWL sfml-system sfml-window sfml-graphics sfml-audio sfml-network)