set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 根据QT版本拼接环境变量字符串QTx_CMAKE_PREFIX_PATH
set(QT_VERSION_MAJOR 5)
set(QT_CMAKE_PREFIX_PATH "QT${QT_VERSION_MAJOR}_CMAKE_PREFIX_PATH")
message(STATUS "QT_VERSION_MAJOR : ${QT_VERSION_MAJOR}")
message(STATUS "QT_CMAKE_PREFIX_PATH : ${QT_CMAKE_PREFIX_PATH}")

# 查找环境变量QTx_CMAKE_PREFIX_PATH。
# 该变量为Qt编译器路径，如Qt\Qt6.5.3\6.5.3\mingw_64
if (NOT DEFINED ENV{${QT_CMAKE_PREFIX_PATH}})
    message(FATAL_ERROR "Not define environment variable:QT_CMAKE_PREFIX_PATH")
endif ()

set(CMAKE_PREFIX_PATH $ENV{${QT_CMAKE_PREFIX_PATH}})
message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/game_info/cell.h
        ${PROJECT_SOURCE_DIR}/game_info/check_unit.h
        ${PROJECT_SOURCE_DIR}/game_info/check_unit.cc
        ${PROJECT_SOURCE_DIR}/game_info/chess_board.h
        ${PROJECT_SOURCE_DIR}/game_info/chess_board.cc
)

set(QT_UI
        forms/main_window.cc
        forms/main_window.h
        forms/main_window.ui
        forms/cell_widget.cc
        forms/cell_widget.h
        forms/cell_widget.ui
)

add_executable(${PROJECT_NAME} main.cc ${SOURCES} ${QT_UI})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION_MAJOR}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
