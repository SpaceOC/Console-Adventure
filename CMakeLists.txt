cmake_minimum_required(VERSION 3.11)
project(ConsoleAdventure)
set(CMAKE_BUILD_TYPE Release)
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)
set(CMAKE_CXX_STANDARD 17)
include_directories(headers)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

set(GAME_INITS_DIR ${CMAKE_SOURCE_DIR}/game)

set(GAME_INITS_CPP_FILES ${GAME_INITS_DIR}/Helper.cpp
                        ${GAME_INITS_DIR}/Textures.cpp
                        ${GAME_INITS_DIR}/Map.cpp
                        ${GAME_INITS_DIR}/Player.cpp
                        ${GAME_INITS_DIR}/ItemManager.cpp
                        ${GAME_INITS_DIR}/BattleMode.cpp
)

#add_library(CA SHARED
add_executable(CA
                ${SOURCE_DIR}/other/settings.cpp
                ${GAME_INITS_CPP_FILES}
                ${SOURCE_DIR}/game.cpp
                #${SOURCE_DIR}/SpaceDOS.cpp
                ${SOURCE_DIR}/main.cpp)

target_compile_options(CA
    PUBLIC
        -O2
        -Wall
        -Wextra
        #-Werror
        -Wpedantic
        -static
)