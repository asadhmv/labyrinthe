#ifndef FONCTION_RESOUDRE2_H
#define FONCTION_RESOUDRE2_H

#include "graph.h"

int compteur_noeuds(int **lab, int taille);
void afficher_lab_noeuds( int **lab, int taille);
void liaison_noeuds(Graph graph,int **lab, int taille);
void bfs(Graph graph, int startVertex, int *solve);
void afficher_lab_solution( int **lab, int taille, int *solve);
int isHere(int *tab, int x, int end);
void lab_solution( int **lab, int taille, int *solve, int end);




#endif