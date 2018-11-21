#include <stdio.h>
#include <curses.h>
#include "logging/log.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>




//mala mapa 17y-18x =306 znakov , velka 34*69=1326


typedef struct mapa{
    char** velkost;
    int x;
    int y;
}MAPA;



typedef struct bomba{
    int x_Position;
    int y_Position;
    char znak;
    char farba;


}BOMBA;

typedef struct hrac{
    int x_Position;
    int y_Position;
    char znak;
    char farba;
    BOMBA * bomba;
    int smer;

}HRAC;
/**
 * alokovanie pamete pre mapu
 * @param m riadok
 * @param n stlpec
 * @return smernik dvojrozmerne pole
 */
char** createM(int m, int n) {
    char **mat;
    mat = malloc(m * sizeof (*mat));
    for (int i = 0; i < m; i++) {
        mat[i] = calloc(n, sizeof (char));
    }
    return mat;
}
/**
 * Uvolnenie pamete pre mapu
 * @param m
 * @param mat
 */
void deletM(int m, char ***mat) {
    for (int i = 0; i < m; i++) {
        free((*mat)[i]);
    }
    free((*mat));
    *mat = NULL;

}

/**
 * Allokovanie pamate pre structuru mapa
 * @return
 */
MAPA *alloc_Mapa()
{
    MAPA *p_mapa = (MAPA *) malloc(sizeof(MAPA));
    if (p_mapa == NULL)
    {
        printf("Nedostatok pamete pre vytvorenie struktury mapa.\n");
        exit(1);
    }
    return p_mapa;
}
/**
 *
 * Allokovanie pamete pre vytvorenie struktury hrac
 */
HRAC *alloc_Hrac()
{
    HRAC *p_hrac = (HRAC *) malloc(sizeof(HRAC));
    if (p_hrac == NULL)
    {
        printf("Nedostatok pamete pre vytvorenie struktury hrac.\n");
        exit(1);
    }
    return p_hrac;
}

BOMBA *alloc_Bomba()
{
    BOMBA *p_bomba = (BOMBA *) malloc(sizeof(BOMBA));
    if (p_bomba == NULL)
    {
        printf("Nedostatok pamete pre vytvorenie struktury hrac.\n");
        exit(1);
    }
    return p_bomba;
}

void zmenavMape(MAPA *mapa,int py,int px,char c){
//    mapa->velkost[(py*2)][(px*4)] = (char)c;
//    mapa->velkost[(py*2)][(px*4)+1] = (char)c;
//    mapa->velkost[(py*2)][(px*4)+2] = (char)c;
//    mapa->velkost[(py*2)][(px*4)+3] = (char)c;
//
//    mapa->velkost[(py*2)+1][(px*4)] = (char)c;
//    mapa->velkost[(py*2)+1][(px*4)+1] = (char)c;
//    mapa->velkost[(py*2)+1][(px*4)+2] = (char)c;
//    mapa->velkost[(py*2)+1][(px*4)+3] = (char)c;

    mapa->velkost[(py)][(px)] = c;

}

void zistiVelkostMapy(char *menoMapy,MAPA * mapa){
    FILE *file;
    file = fopen(menoMapy, "r");
    int c;

    mapa->x=0;
    mapa->y=0;
    while ((c = fgetc(file)) != EOF)
    {

        mapa->x++;
        if(c=='\n')
        {
            mapa->y++;
        }

    }
    fclose(file);



};


void nacitajMapu(MAPA * mapa,char *menoMapy){

   FILE * subor;
   subor = fopen(menoMapy, "r");

//   mapa->x=((mapa->x)/(mapa->y+1))*4+1;
//   mapa->y=(mapa->y+1)*2;

    mapa->x=((mapa->x)/(mapa->y+1))+1;
    mapa->y=(mapa->y+1);
   printf("%d %d ",mapa->x,mapa->y);
   int px=0,py=0;
   mapa->velkost = createM(mapa->y,mapa->x);
    int c;
    while ((c = fgetc(subor)) != EOF)
    {
        zmenavMape(mapa,py,px,(char)c);
        px++;
        if(c == '\n'){

            py++;
            px=0;
        }
    }
    fclose(subor);

}

/**
 * Funckia na bratie signalu z klavesnica
 * @param signal
 * @return
 */


void vykresliMapu(MAPA * mapa){
 char pom[1];

    for (int y = 0; y < mapa->y; y++){
         for (int x = 0; x < mapa->x; x++) {
    pom[0] = mapa->velkost[y][x];
           // mvprintw(y+1,x+1,&pom[0]);
             mvprintw((y*2),(x*4),&pom[0]);
             mvprintw((y*2),(x*4)+1,&pom[0]);
             mvprintw((y*2),(x*4)+2,&pom[0]);
             mvprintw((y*2),(x*4)+3,&pom[0]);

             mvprintw((y*2)+1,(x*4),&pom[0]);
             mvprintw((y*2)+1,(x*4)+1,&pom[0]);
             mvprintw((y*2)+1,(x*4)+2,&pom[0]);
             mvprintw((y*2)+1,(x*4)+3,&pom[0]);
                }
    }

}
void odpocetBomby(MAPA * mapa, HRAC * hrac){




}

void vytvorBombu(MAPA * mapa, HRAC * hrac){
    hrac->bomba=alloc_Bomba();
    hrac->bomba->y_Position=hrac->y_Position;
    hrac->bomba->x_Position=hrac->x_Position;
    hrac->bomba->znak = '*';
    zmenavMape(mapa,hrac->bomba->y_Position,hrac->bomba->x_Position,hrac->bomba->znak);


}

void pohybHraca(MAPA * mapa, HRAC * hrac) {

    switch (hrac->smer) {
        case 'a':
            if (mapa->velkost[hrac->y_Position][hrac->x_Position-1] == ' ') {
                zmenavMape(mapa, hrac->y_Position, hrac->x_Position, ' ');
                hrac->x_Position--;
                zmenavMape(mapa, hrac->y_Position, hrac->x_Position, hrac->znak);
                hrac->smer = 0;
            }

            break;
        case 'w':
            if (mapa->velkost[hrac->y_Position-1][hrac->x_Position] == ' ') {
                zmenavMape(mapa, hrac->y_Position, hrac->x_Position, ' ');
                hrac->y_Position--;
                zmenavMape(mapa, hrac->y_Position, hrac->x_Position, hrac->znak);
                hrac->smer = 0;

                break;
                case 's':
                    if (mapa->velkost[hrac->y_Position+1][hrac->x_Position] == ' ') {
                        zmenavMape(mapa, hrac->y_Position, hrac->x_Position, ' ');
                        hrac->y_Position++;
                        zmenavMape(mapa, hrac->y_Position, hrac->x_Position, hrac->znak);
                        hrac->smer = 0;
                    }
                break;
                case 'd':
                    if (mapa->velkost[hrac->y_Position][hrac->x_Position+1] == ' ') {
                        zmenavMape(mapa, hrac->y_Position, hrac->x_Position, ' ');
                        hrac->x_Position++;
                        zmenavMape(mapa, hrac->y_Position, hrac->x_Position, hrac->znak);
                        hrac->smer = 0;
                    }
                break;
                case ' ':
                    vytvorBombu(mapa,hrac);

                    break;
                default:
                    break;
            }

    }
}


void *delay(void * input) {
    do {
        ((struct hrac*)input)->smer = getchar();

    } while (1);

}

void vytvorVlaknoHraca(void *(*startovaciaFunkcia)(void *),HRAC * hrac) {
    pthread_t vlakno;
    pthread_create(&vlakno, 0, startovaciaFunkcia, hrac);
}

void vytvorVlaknoPreBombu(void *(*startovaciaFunkcia)(void *),MAPA * mapa,HRAC * hrac) {
    pthread_t vlakno;
    pthread_create(&vlakno, 0, startovaciaFunkcia, hrac);
}





int main() {





//    log_set_quiet(0);
//    log_set_level(LOG_DEBUG);
//    FILE *logFile = fopen("logs.log","w+");
//    log_set_fp(logFile);
//
//
//    if (logFile == NULL){
//        printf("Error! opening file");
//        // Program exits if the file pointer returns NULL.
//        return 1;
//    }

//    log_trace(const char *fmt, ...);
//    log_debug(const char *fmt, ...);
//    log_info(const char *fmt, ...);
//    log_warn(const char *fmt, ...);
//    log_error(const char *fmt, ...);
//    log_fatal(const char *fmt, ...);

    // log_debug("Hello %s", "world");
    //log_info("Hello %s", "world");
    //log_warn("Hello %s", "world");
    // log_error("Hello %s", "world");

    initscr(); // Initialize the window
    noecho(); // Don't echo any keypresses
    curs_set(FALSE); // Don't display a cursor


    MAPA *mapa = alloc_Mapa();
    zistiVelkostMapy("mapa.txt",mapa);
    nacitajMapu(mapa,"mapa.txt");
    HRAC *hrac=alloc_Hrac();
    hrac->x_Position=15;
    hrac->y_Position=15;
    hrac->znak='H';
    hrac->smer = '0';
    zmenavMape(mapa,hrac->y_Position,hrac->x_Position,hrac->znak);
    printf("\n");


vytvorVlaknoHraca(delay,hrac);

    while(1) {

        pohybHraca(mapa,hrac);
        vykresliMapu(mapa);
        refresh();


    }
endwin();


}