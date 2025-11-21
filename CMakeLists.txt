cmake_minimum_required(VERSION 3.20)
project(backpack VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
        src/main.c
        src/commands.c
        src/utils.c
)

add_executable(backpack ${SOURCES})

install(TARGETS backpack
        RUNTIME DESTINATION bin)
