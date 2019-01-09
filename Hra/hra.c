//
// Created by sterb on 9. 1. 2019.
//
#include "hra.h"

/**
 * Funkcia allokuje pamät pre mapu
 * @param m - pocet riadkov
 * @param n - pocet stlpcov
 * @return - vrati smernik na prvy prvok pola
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
