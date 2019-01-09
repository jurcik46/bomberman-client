cmake_minimum_required(VERSION 3.10)
project(bomberman_client C)

set(CMAKE_C_STANDARD 99)
link_libraries(ncurses)
link_libraries(pthread)

add_executable(bomberman_client main.c logging/log.c logging/log.h communication.c communication.h Menu/menu.c Menu/menu.h constants.h Hra/hra.c Hra/hra.h Hra/mapa.c Hra/mapa.h Hra/gameConstants.h)
target_link_libraries(bomberman_client pthread)

