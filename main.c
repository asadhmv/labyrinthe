#include <stdio.h>
#include "generateur.c"
#include "generateur.h"
#include "fonction_resoudre2.h"
#include "graph.h"
#include "graph.c"
#include "file.h"
#include "queue.h"


//***********************************************************************************************************

//                                  FONCTION   MAIN 

//***********************************************************************************************************

int main(void)
{
    int **lab;
    int TAILLE;

    printf("Veuillez choisir la taille du labyrinthe: ");
    scanf(" %i",&TAILLE);
    if(TAILLE % 2==0)           //Si c'est un nombre pair, on ajoute 1 pour les murs d'en bas
        TAILLE = TAILLE + 1;

    printf("\n\t\t\t\tVoici un labyrinthe de cette taille choisie\n\n");
    lab=creation_lab1(TAILLE);
    creation_grille(lab,TAILLE);
    lab_generation(lab,TAILLE);
    //afficher_lab2(lab,TAILLE);
    afficher_lab_noeuds(lab, TAILLE);
    

    int n = compteur_noeuds(lab, TAILLE);
    printf("\n\n\nVoici les %d noeuds\n\n", n);
    afficher_lab_noeuds(lab, TAILLE);

    Graph graph = new_graph(n, false);
    add_edge(graph, 1, 2);
    add_edge(graph, n, n-1);
    liaison_noeuds(graph, lab, TAILLE);

    int solve[graph->nb_vertices];
    bfs(graph, 1, solve);

    
    printf("\n\n\nVoici la solution du labyrinthe\n\n\n");

    lab_solution(lab, TAILLE, solve, n);
    //afficher_lab_solution(lab, TAILLE, solve);
    afficher_lab_noeuds(lab, TAILLE);


    erase_graph(graph);
    liberer_lab(lab,TAILLE);

    return 0;
}