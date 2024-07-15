cmake_minimum_required(VERSION 3.28)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_CONSOLE_UI "Use console for game" ON)

if (USE_CONSOLE_UI)
    add_subdirectory(game_ui/console)
else ()
    add_subdirectory(game_ui/qt)
endif ()
