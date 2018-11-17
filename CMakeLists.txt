cmake_minimum_required(VERSION 3.10)
project(bomberman_client C)

set(CMAKE_C_STANDARD 99)
link_libraries(ncurses)

add_executable(bomberman_server main.c logging/log.c logging/log.h)

