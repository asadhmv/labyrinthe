#ifndef GENERATEUR_H
#define GENERATEUR_H


typedef enum{faux,vrai}booleen;

booleen verifier_lab_termine(int **lab, int taille);     //Verifie si toutes les cases PASSAGE ont le même nombre
int **creation_lab1(int taille);                         //Allocation dynamique d'un tableau 2 dimenions int
booleen **creation_booleen_lab1(int taille);             //Allocation dynamique d'un tableau 2 dimenions booleen
void creation_grille(int **lab, int taille);
void lab_generation(int **lab, int taille);
void afficher_lab(int **lab, int taille);
void afficher_lab2(int **lab, int taille);
void liberer_lab(int **lab, int taille);


#endif