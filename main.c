//    log_trace(const char *fmt, ...);
//    log_debug(const char *fmt, ...);
//    log_info(const char *fmt, ...);
//    log_warn(const char *fmt, ...);
//    log_error(const char *fmt, ...);
//    log_fatal(const char *fmt, ...);

//    log_debug("Hello %s", "world");
//    log_info("Hello %s", "world");
//    log_warn("Hello %s", "world");
//    log_error("Hello %s", "world");

#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>
#include "Menu/menu.h"
#include <string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
    wrefresh(local_win);		/* Show that box 		*/

    return local_win;
}



int main() {

//    log_set_quiet(0);
//    log_set_level(LOG_DEBUG);
//    FILE *logFile = fopen("logs.log", "w+");
//    log_set_fp(logFile);
//
//    if (logFile == NULL) {
//        printf("Error! opening file");
//        // Program exits if the file pointer returns NULL.
//        return 1;
//    }

    WINDOW *my_window;
    int startX, startY, width, heigh;

    initscr();
    cbreak();

    heigh = 20;
    width = 24;
    startX = (COLS - width) / 2;
    startY = (LINES - heigh) / 2;

    refresh();
    my_window = newwin(heigh, width, startY, startX);
    keypad(my_window, true);
    wprintw(my_window, "\n\tBOMBERMAN\n\n");
    wprintw(my_window, "\t  MENU\n");
    wprintw(my_window, "________________________\n");
    //wborder(my_window,'|','|','-','-','+','+','+','+');
    wrefresh(my_window);
    mainMenu(my_window);
    wrefresh(my_window);

    refresh();
    getch();
    endwin();


//        box(stdscr,0,0);
//        wborder(stdscr,'|','|','-','-','+','+','+','+');
//        refresh();
//        getch();
//        endwin();

    //fclose(logFile);
    return 0;
}

