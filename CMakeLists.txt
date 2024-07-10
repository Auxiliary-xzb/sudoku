cmake_minimum_required(VERSION 3.28)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        game_info/room.h
        game_info/check_unit.h
        game_info/check_unit.cc
        game_info/chess_board.h
        game_info/chess_board.cc
        game_ui/console/console_game.cc
        game_ui/console/console_game.h
)

set(CONSOLE_UI
        game_ui/console/console_game.cc
        game_ui/console/console_game.h
)

set(UI_SOURCES ${CONSOLE_UI})

add_executable(${PROJECT_NAME} main.cc ${SOURCES} ${UI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
