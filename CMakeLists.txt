cmake_minimum_required(VERSION 4.3)
project(snake)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/main.hpp src/app/snkApp.cpp src/app/snkApp.hpp
        src/console/snkConsole.hpp
        src/console/snkConsole.cpp
        src/console/snkWinConsole.hpp
        src/console/snkWinConsole.cpp
        src/console/snkLinConsole.hpp
        src/console/snkLinConsole.cpp
        src/game/screens/snkState.hpp
        src/game/screens/snkState.cpp
        src/game/screens/snkMenu.hpp
        src/game/screens/snkMenu.cpp
        src/game/screens/snkGame.hpp
        src/game/screens/snkGame.cpp
        src/game/screens/snkNick.hpp
        src/game/screens/snkNick.cpp
        src/game/screens/snkRecs.hpp
        src/game/screens/snkRecs.cpp
        src/game/snkDatabase.hpp
        src/game/snkDatabase.cpp
        src/game/snkLevel.hpp
        src/game/snkLevel.cpp
        src/game/snkSnake.hpp
        src/game/snkSnake.cpp
        src/log/snkLog.hpp)

include_directories(inc/pdcurses inc/sqlite src src/app src/console src/game src/game/screens)

add_executable(snake ${SOURCE_FILES})

target_link_directories(snake PRIVATE ${CMAKE_SOURCE_DIR}/lib/win/x64)
set(sqlite_dir "${CMAKE_CURRENT_SOURCE_DIR}/dll/win/x64")
set(sqlite_dll "${sqlite_dir}/sqlite3.dll")
if(MSVC)
    set(sqlite_library "${CMAKE_CURRENT_BINARY_DIR}/sqlite3.lib")
    add_custom_command(
        OUTPUT "${sqlite_library}"
        COMMAND "${CMAKE_AR}" /nologo /machine:x64 /name:sqlite3.dll
                "/def:${sqlite_dir}/sqlite3.def" "/out:${sqlite_library}"
        DEPENDS "${sqlite_dir}/sqlite3.def"
        VERBATIM)
    add_custom_target(sqlite_import_library DEPENDS "${sqlite_library}")
    add_dependencies(snake sqlite_import_library)
else()
    # MinGW can link directly against the DLL.
    set(sqlite_library "${sqlite_dll}")
endif()

target_link_libraries(snake PRIVATE pdcurses "${sqlite_library}")
add_custom_command(TARGET snake POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${sqlite_dll}" "$<TARGET_FILE_DIR:snake>"
    VERBATIM)
