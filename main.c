#include <stdio.h>
#include <curses.h>
#include "logging/log.h"

int main() {

    log_set_quiet(0);
    log_set_level(LOG_DEBUG);
    FILE *logFile = fopen("logs.log","w+");
    log_set_fp(logFile);

    if (logFile == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        return 1;
    }

//    log_trace(const char *fmt, ...);
//    log_debug(const char *fmt, ...);
//    log_info(const char *fmt, ...);
//    log_warn(const char *fmt, ...);
//    log_error(const char *fmt, ...);
//    log_fatal(const char *fmt, ...);

    log_debug("Hello %s", "world");
    log_info("Hello %s", "world");
    log_warn("Hello %s", "world");
    log_error("Hello %s", "world");


    initscr();			/* Start curses mode 		  */
    printw("Hello Wdsadasdorld !!!");	/* Print Hello World		  */
    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
    endwin();

    fclose(logFile);
    return 0;
}