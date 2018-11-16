#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#define DELAY 30000

void nacitajMapu(){
    FILE * vstup;
    if ((vstup = fopen("mapa.txt", "r")) == NULL)
    {
    int riadok,stlpec;
    while();

}

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

void deletM(int m, char*** mat) {
    for (int i = 0; i < m; i++) {
        free((*mat)[i]);
    }
    free((*mat));
    *mat = NULL;

}

int main(int argc, char *argv[]) {

}