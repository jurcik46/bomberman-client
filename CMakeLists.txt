cmake_minimum_required(VERSION 3.10)
project(bomberman_client C)

set(CMAKE_C_STANDARD 99)
link_libraries(ncurses)

add_executable(bomberman_client main.c logging/log.c logging/log.h communication.c communication.h)
add_executable(bomberman_client main.c logging/log.c logging/log.h Menu/menu.c Menu/menu.h)

