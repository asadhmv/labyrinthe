#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generateur.h"

/*
void creation_lab(int **tab, int taille)  //Allocation dynamique d'un tableau 2 Dimensions pour la creation du labyrinthe
{ 
    *tab=(int*)malloc(taille*sizeof(int));
    for(int i=0; i<taille ; i++)
    {
        tab[i] =malloc(taille*sizeof(int));
    }   
}

int **creation(int taille)
{
    int **t;
    int i,j;
    t=(int**)malloc(taille*sizeof(int*));
    for(i=0 ; i<taille ;i++)
        t[i]=(int*)malloc(taille*sizeof(int));

    return t;
}*/



booleen verifier_lab_termine(int **lab, int taille)//Verifie si toutes les cases CHEMIN ont le même nombre
{
    int i,j;
    for (i=1 ;i<taille-1 ; i+=2)
    {
        for (j=1; j<taille-1; j+=2)
        {
            if (lab[i][j] != lab[1][1] )
                return faux;// Tant que toutes les cases CHEMIN n'ont pas le meme nombre fonction retourne Faux=0
        }
    }

    return vrai;       // Tant que toutes les cases CHEMIN n'ont pas le meme nombre fonction retourne Vrai=1
}

int **creation_lab1(int taille)         //Allocation dynamique d'un tableau 2 dimenions
{
    int **lab;
    int i,j;

    lab=(int**)calloc(taille,sizeof(int*));
     
    for(i=0 ; i<taille ; i++)
    {
        *(lab+i)=(int*)calloc(taille,sizeof(int));
        for(j=0 ; j<taille ; j++) 
            lab[i][j]=0; //pour initialiser à 0=MUR
    }
   
     
    return lab;   
}

booleen **creation_booleen_lab1(int taille)         //Allocation dynamique d'un tableau 2 dimenions
{
    booleen **lab;
    int i,j;

    lab=(booleen**)calloc(taille,sizeof(int*));
     
    for(i=0 ; i<taille ; i++)
    {
        *(lab+i)=(booleen*)calloc(taille,sizeof(int));
        for(j=0 ; j<taille ; j++) 
            lab[i][j]=0; //pour initialiser à 0=MUR
    }
   
     
    return lab;   
}

void creation_grille(int **lab, int taille)
{
    int nb = 0;
    int i,j;
    for(i=1 ; i<taille ; i+=2)
    {   
        for(j=1 ; j<taille ; j+=2)
            lab[i][j]=1;            
    }
    for (i=0 ; i<taille ; i++)
    {
        for (j=0 ; j<taille ; j++)
        {
            if (lab[i][j]==1)
            {
                nb++;
                lab[i][j]=nb;
            }
        }
    }
    lab[1][0]=1;                //Creation d'entrée 
    lab[taille-2][taille-1]=1;  //Creation de la sortie
}

void lab_generation(int **lab, int taille)
{
    int i,j;
    srand(time(NULL));// Initialisation de la donnée seed: Pour generer des nombres pseudo-aléatoires

    while (verifier_lab_termine(lab, taille) == faux){//Tant que toutes les cases PASSAGE n'ont pas la meme nombre

//*************** Choix d'un mur au hazard***************************************************     
        int x = rand() % (taille - 2) + 1; //nb1 % nb2 = reste de la division euclidienne
                                           //+1 permet d'avoir comme MIN = 1 et MAX = taille-2
                                           // rand  renvoie un nombre calculé à partir de la donnée seed

        int y;

        if (x % 2 == 0) // Si x est un multiple de 2 ou nombre pair, la ligne sera remplie de murs 
            y = ((rand() % ((taille - 1) / 2))) * 2 + 1;// MAX = (taille - 1) / 2    MIN = 1

        else// si x est impair, il y a des cases mur, vide consécutifs
            y = ((rand() % ((taille - 2) / 2))) * 2 + 2;// MAX = (taille - 2) / 2    MIN = 2
//********************************************************************************************
        int voisin1;
        int voisin2;

        if (lab[x-1][y]==0)
        {
            voisin1 = lab[x][y-1];
            voisin2 = lab[x][y+1];
        }

        else
        {
            voisin1 = lab[x-1][y];
            voisin2 = lab[x+1][y];
        }

        if (voisin1 != voisin2)  //Vérifions si le nombre des 2 cotés du mur sont différents
        {
            lab[x][y] = 1;   //On casse le mur
            

            for (int i = 1; i < taille - 1; i += 2)
            {
                for (int j = 1; j < taille - 1; j += 2)
                {
                    if (lab[i][j] == voisin2)
                        lab[i][j] = voisin1;      //On rempli le voisin1 avec la valeur du voisin2
                }
            }
        }
    }
    for (i=0 ;i<taille-1 ; i++)
    {
        for (j=0; j<taille-1; j++)
        {
            if (lab[i][j] != 0)
                lab[i][j]=1;
        }
    }            
}

void afficher_lab(int **lab, int taille)
{
    int i,j,k;
    
    for(i=0 ; i<taille ; i++) 
    {
        for(j=0 ; j<taille ; j++) 
        {    
                if(j == (taille-1))
                    printf(" %d \n", *(*(lab+i)+j) );             
                else 
                    printf(" %d ", *(*(lab+i)+j) );    
        }
    }
}

void afficher_lab2(int **lab, int taille)
{
    int i,j,k;
    
    for(i=0 ; i<taille ; i++) 
    {
        for(j=0 ; j<taille ; j++) 
        {    
            if(lab[i][j] != 1)
            {    
                if(j == (taille-1))
                    printf("%d \n", *(*(lab+i)+j) );             
                else 
                    printf("%d ", *(*(lab+i)+j) );
            }
            else if(lab[i][j] == 1)
            {    
                if(j == (taille-1))
                    printf("  \n");
                else
                    printf("  ");
            }
        }
    }
}

void liberer_lab(int **lab, int taille)
{
    for(int i = 0; i < taille; ++i)
        free(lab[i]);

    free(lab);
}



//***********************************************************************************************************

//                                  PARTIE   RESOLUTION 

//***********************************************************************************************************

// Résout le labyrinthe
/*
void resoudre_lab(int **lab, int taille)  //Le chemin sera affiche par la valeur 2
{
    int x=1;
    int y=1;

    lab[1][0]=2;                       //Remplace l'entree par 2 et la sortie par 5
    lab[taille - 2][taille - 1]=5;

    booleen **dejaVisite = creation_booleen_lab1(taille);

    for(int i = 1; i < taille -1; i++)
    {
        for(int i = 1; i < taille -1; i++)
            dejaVisite = faux;
    }

    dejaVisite[1][0] = vrai; 

    while(x != taille-1 && y != taille-1)
    {
        int droite = lab[x][y + 1];      //Case de droite
        int gauche = lab[x][y - 1];      //Case de gauche
        int haut = lab[x - 1][y];        //Case du haut
        int bas = lab[x + 1][y];         //Case du bas


        if(droite+gauche+haut+bas >= 7)             //Case avant la sortie
        {
            dejaVisite[x][y]=vrai;
            lab[x][y]=2;
            y = y + 1;
            lab[x][y]=2;
            dejaVisite[x][y]=vrai;

        }
        else if (droite+gauche+haut+bas == 5)              // 4 Directions Possibles
        {   
            dejaVisite[x][y]=vrai;
            lab[x][y]=2;                            // Ici on respecte la regle de la main droite

            if(gauche == 2)
            {  
                if(dejaVisite[x + 1][y] == faux) 
                    x = x + 1;
                if(dejaVisite[x + 1][y] == vrai)
                    y = y + 1;
                if(dejaVisite[x + 1][y] == vrai && dejaVisite[x][y + 1] == vrai)
                    x = x - 1;                                  
            else if(droite == 2)
            {    
                if(dejaVisite[x - 1][y] == faux) 
                    x = x - 1;
                if(dejaVisite[x - 1][y] == vrai)
                    y = y - 1;
                if(dejaVisite[x - 1][y] == vrai && dejaVisite[x][y - 1] == vrai)
                    x = x + 1;
            }    
            else if(haut == 2)
            {    
                if(dejaVisite[x][y-1] == faux) 
                    y = y - 1;
                if(dejaVisite[x][y-1] == vrai)
                    x = x + 1;
                if(dejaVisite[x + 1][y] == vrai && dejaVisite[x][y-1] == vrai)
                    y = y + 1;
            }    
            else if(bas == 2)
            {     
                if(dejaVisite[x][y + 1] == faux) 
                    y = y + 1;
                if(dejaVisite[x][y + 1] == vrai)
                    x = x - 1;
                if(dejaVisite[x - 1][y] == vrai && dejaVisite[x][y + 1] == vrai)
                    y = y - 1;
            }
            lab[x][y]=2;
            dejaVisite[x][y]=vrai;
        }    
        else if (droite+gauche+haut+bas == 4)         // 3 Directions Possibles
        {
            dejaVisite[x][y]=vrai;
            lab[x][y]=2;
            if(gauche == 2)
            {
                if(bas == 1)
                {   
                    if(dejaVisite[x + 1][y] == faux) 
                        x = x + 1;
                    else if(dejaVisite[x + 1][y] == vrai && droite == 1)
                        y = y + 1;
                    else if(dejaVisite[x + 1][y] == vrai && droite != 1)
                        x = x - 1;
                }
                else
                {  
                    if(dejaVisite[x][y + 1] == faux)  
                        y = y + 1;
                    else
                        x = x - 1; 
                }
            }                   
            if(droite == 2)
            {
                if(haut == 1)
                {
                    if(dejaVisite[x - 1][y] == faux) 
                        x = x - 1;
                    else if(dejaVisite[x - 1][y] == vrai && gauche == 1)
                        y = y - 1;
                    else if(dejaVisite[x - 1][y] == vrai && gauche != 1)
                        x = x + 1;
                }
                else
                {
                    if(dejaVisite[x][y - 1] == faux)  
                        y = y - 1;
                    else
                        x = x + 1; 
                }                        
            }    
            if(haut == 2)
            {
                if(gauche == 1)
                {
                    if(dejaVisite[x][y - 1] == faux) 
                        y = y - 1;
                    else if(dejaVisite[x][y - 1] == vrai && bas == 1)
                        x = x + 1;
                    else if(dejaVisite[x][y - 1] == vrai && bas != 1)
                        y = y + 1;
                }
                else
                {
                    if(dejaVisite[x + 1][y] == faux)  
                        x = x + 1;
                    else
                        y = y + 1;
                }
            }
            if(bas == 2)
            {
                if(droite == 1)
                {
                    if(dejaVisite[x][y + 1] == faux) 
                        y = y + 1;
                    else if(dejaVisite[x][y + 1] == vrai && haut == 1)
                        x = x - 1;
                    else if(dejaVisite[x][y + 1] == vrai && haut != 1)
                        y = y - 1;
                }
                else
                {
                    if(dejaVisite[x - 1][y] == faux)  
                        x = x - 1;
                    else
                        y = y - 1;
                }
            }

            lab[x][y]=2;
            dejaVisite[x][y]=vrai;
        }   
        else if (droite+gauche+haut+bas == 3)         // Couloir = 2 Directions Possibles
        {
            dejaVisite[x][y]=vrai;
            lab[x][y]=2;
            if(gauche == 1)
                y = y - 1;    
            if(droite == 1)
                y = y + 1;
            if(haut == 1)
                x = x - 1;
            if(bas == 1)
                x = x + 1;
            
            lab[x][y]=2;
            dejaVisite[x][y]=vrai;
            
        }   
        else if (droite+gauche+haut+bas == 2)         //Impasse = 1 Direction Possible (direction d'arrivee)
        {
            while(droite+gauche+haut+bas != 4 || droite+gauche+haut+bas != 5)
            {
                dejaVisite[x][y]=vrai;
                lab[x][y]=1;
                if(gauche == 2)
                    y = y - 1;           
                if(droite == 2)
                    y = y + 1;    
                if(haut == 2)
                    x = x - 1;
                if(bas == 2)
                    x = x + 1;
                    
                lab[x][y]=1;
                dejaVisite[x][y]=vrai;
                
            }  
        }
    }          
}
}*/

