set(SOURCES
        ${PROJECT_SOURCE_DIR}/game_info/cell.h
        ${PROJECT_SOURCE_DIR}/game_info/check_unit.h
        ${PROJECT_SOURCE_DIR}/game_info/check_unit.cc
        ${PROJECT_SOURCE_DIR}/game_info/chess_board.h
        ${PROJECT_SOURCE_DIR}/game_info/chess_board.cc
        ${PROJECT_SOURCE_DIR}/game_ui/console/console_game.cc
        ${PROJECT_SOURCE_DIR}/game_ui/console/console_game.h
)

set(CONSOLE_UI
        console_game.h
        console_game.cc
        windows_console.cc
        windows_console.h
)

add_executable(${PROJECT_NAME} main.cc ${SOURCES} ${UI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
