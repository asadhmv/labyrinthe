#include <stdio.h>
#include <stdlib.h>
#include "generateur.h"
#include "fonction_resoudre2.h"
#include "graph.h"
#include "file.h"
#include "queue.h"


int compteur_noeuds(int **lab, int taille)
{
	int i, j, noeuds;

	lab[1][0] = -1;                
    lab[taille-2][taille-1] = -1;
    noeuds = 2;

	int gauche, droite,haut,bas,somme;   


	for(i=1 ; i<taille-1 ; i++)
	{
		for(j=1 ; j<taille-1 ; j++)
		{
			if(lab[i][j] == 1)
			{
				gauche = lab[i][j-1];
				droite = lab[i][j+1];
				haut   = lab[i-1][j];
				bas    = lab[i+1][j];

				somme = gauche + droite + haut + bas;

				if(somme == -1 || somme >= 3 || somme == 1)
				{
					lab[i][j] = -1;
					noeuds = noeuds + 1;
				}
				else if((somme == 2 || somme == 0) && droite != gauche && haut != bas)
				{
					lab[i][j] = -1;
					noeuds = noeuds + 1;
				}
			}
		}	
	}

	return noeuds;
}

void afficher_lab_noeuds( int **lab, int taille)
{
    int i,j,k;
    
    for(i=0 ; i<taille ; i++) 
    {
        for(j=0 ; j<taille ; j++) 
        {    
            if(lab[i][j] == 0)
            {    
                if(j == (taille-1))
                    //printf("%d \n", *(*(lab+i)+j) );
                    printf("■ \n");             
                else 
                    //printf("%d ", *(*(lab+i)+j) );
                	printf("■ ");
            }
            else if(lab[i][j] != 0 && lab[i][j]!= -1)
            {    
                if(j == (taille-1))
                    printf("  \n");
                else
                    printf("  ");
            }
            else if(lab[i][j] == -1)
            {    
                if(j == (taille-1))
                    printf("\033[36m%s\033[00m","♦ \n");
                else
                    printf("\033[36m%s\033[00m","♦ "); //◇♦
            }
        }
    }
}


void liaison_noeuds(Graph graph,int **lab, int taille)
{
	int i,j, ind = 1, k = 0;

	for(i=0 ; i<taille ; i++)
	{
		for(j=0 ; j<taille ; j++)
		{
			if(lab[i][j] == -1)
			{
				lab[i][j] = ind;
				ind++;
			}
		}
	}

	int temp1, temp2;
	temp1=1;
	temp2=1;

	int gauche, droite, haut, bas;


	for(i=1 ; i<taille-1 ; i++)
	{
		for(j=1 ; j<taille-1 ; j++)
		{
			gauche = lab[i][j-1];
			droite = lab[i][j+1];
			haut   = lab[i-1][j];
			bas    = lab[i+1][j];

			if(lab[i][j] >= 2)
			{
					if(gauche != 0 && lab[i][j] != 2)
					{
						k = j - 1;
						while(lab[i][k] < 2){
							k = k -1;
						}

						add_edge(graph, lab[i][j], lab[i][k]);
					}
					if(droite != 0)
					{
						k = j + 1;
						while(lab[i][k] < 2){
							k = k + 1;
						}
						add_edge(graph, lab[i][j], lab[i][k]);
					}
					if(haut != 0)
					{
						k = i - 1;
						while(lab[k][j] < 2){
							k = k - 1;
						}
						add_edge(graph, lab[i][j], lab[k][j]);

					}
					if(bas != 0)
					{
						k = i + 1;
						while(lab[k][j] < 2){
							k++;
						}
						add_edge(graph, lab[i][j], lab[k][j]);

					}
			}
		}
	}
}


//BFS algorithm

void bfs(Graph graph, int startVertex, int *solve) {
  	
  	struct queue* q = createQueue();
  	int i = 1;
  	
  	int tab[graph->nb_vertices];
  	int visited[graph->nb_vertices] ;
  	tab[0] = startVertex;
  	enqueue(q, startVertex);

  	for(int k=0 ; k<graph->nb_vertices ; k++){
  		visited[k]=0;
  		tab[k] = -1;
  		solve[k] = -1;
  	}

  	visited[startVertex-1]=1;
  	NodeList n = graph->tab_neighbours[1].begin;
  	while(n != NULL)
	{
		if(n->value == startVertex)
		{
			n->color = gris;
			break;
		}
		n = n->next;
	}

	while (!isEmpty(q)) 
	{ 
	    int currentVertex = q->items[q->front];
	    visited[currentVertex-1]=1;


	    NodeList node = graph->tab_neighbours[currentVertex-1].begin;
		//node->color = gris;

	    while (node != NULL) 
	    {

	    	if(node->color == 0 && visited[node->value - 1] == 0)
	    	{
	        	enqueue(q, node->value);
	        	tab[node->value - 1] = currentVertex;
	        	//printf("\nEnfiler %i\n", node->value);
	        	node->color = 1;
	      	}
	      	if(node->next == NULL)
	      		break;
	      	else
	      		node = node->next;
	    }

	    node->color = 2;
	    currentVertex = dequeue(q);
	    if(currentVertex == graph->nb_vertices)
	    	break;
  	}



  	i= graph->nb_vertices -1;
  	int j = graph->nb_vertices -1;
  	solve[i] = graph->nb_vertices;
  	i--;
  	while(tab[j] != 1)
  	{
  		solve[i]= tab[j];
  		j = solve[i] -1;
  		i--;
  	}

  	solve[i] = 1;
}

void afficher_lab_solution( int **lab, int taille, int *solve)
{
    int i,j,k, l = 0;
    int distance;

    while(solve[l]<2)
     	l++;
    
    int gauche, droite, haut, bas;

    for(i=1 ; i<taille-1 ; i++)
    {
    	for(j=1 ; j<taille-1 ; j++)
   		{
   			gauche = lab[i][j-1];
			droite = lab[i][j+1];
			haut   = lab[i-1][j];
			bas    = lab[i+1][j];

    		if(lab[i][j] == solve[l])
    		{
    			l++;
    			lab[i][j] = -1;

    			if(gauche != 0)
				{
					k = j - 1;
					while(lab[i][k]  != 0){
						if(lab[i][k] == solve[l])
						{
							for(distance = j-1; distance>k ; distance--)
								lab[i][distance] = -1;
							break;

						}
						k = k -1;
					}
				}
				if(droite != 0)
				{
					k = j + 1;
					while(lab[i][k] != 0){
						if(lab[i][k] == solve[l])
						{
							for(distance = j+1; distance<k ; distance++)
								lab[i][distance] = -1;
							break;

						}
						k = k + 1;
					}
				}
				if(haut != 0)
				{
					k = i - 1;
					while(lab[k][j] != 0){
						if(lab[k][j] == solve[l])
						{
							for(distance = i-1; distance>k ; distance--)
								lab[distance][j] = -1;
							break;
						}
						k = k - 1;
					}
				}
				if(bas != 0)
				{
					k = i + 1;
					while(lab[k][j] != 0){
						if(lab[k][j] == solve[l])
						{
							for(distance = i+1; distance<k ; distance++)
								lab[distance][j] = -1;
							break;
						}
						k++;
					}
    			}
    		}
    	}
	}
}

int isHere(int *tab, int x, int end)
{
	for(int i=0 ; tab[i]!= end ; i++)
	{
		if(tab[i] == x)
			return 1;
	}
	if(end == x)
		return 1;

	return 0;
}

void lab_solution( int **lab, int taille, int *solve, int end)
{
    int i = 1,j = 1,k = 0, l=0;
    int distance;

    while(*solve != 1){
    	solve++;
    }
    *solve = 2;

    lab[1][0] = -1;
    lab[1][1] = -1;


    int **visited = creation_lab1(taille);

    for(int x=0 ; x <taille ; x++)
    {
    	for(int y=0 ; y<taille ; y++)
    	{
    		if(lab[x][y] == 0)
    			visited[x][y] = 1;
    	}
    }
    visited[1][0] = 1;
    visited[1][1] = 1;

    int gauche, droite, haut, bas;

    //while(lab[i][j] != end)
    //{

		for(int m=0 ; m<end ; m++)
		{
    	gauche = lab[i][j-1];
		droite = lab[i][j+1];
		haut   = lab[i-1][j];
		bas    = lab[i+1][j];


		if(gauche != 0 && lab[i][j] != 2 && visited[i][j-1] != 1)
		{
			k = j - 1;
			while(lab[i][k]  != 0 && visited[i][k] != 1)
			{
				visited[i][k] = 1;
				if(isHere(solve,lab[i][k], end))
				{
					for(distance = j-1; distance>=k ; distance--)
						lab[i][distance] = -1;
					j = k;
					break;
				}
				k = k -1;
			}
			if(isHere(solve,lab[i][k], end))
				continue;
		}
		if(droite != 0 && visited[i][j+1] != 1)
		{
			k = j + 1;
			while(lab[i][k] != 0 && visited[i][k] != 1)
			{
				visited[i][k] = 1;
				if(isHere(solve,lab[i][k], end))
				{
					for(distance = j; distance<=k ; distance++)
						lab[i][distance] = -1;
					j = k;
					break;
				}
				k = k + 1;
			}
			if(isHere(solve,lab[i][k], end))
				continue;
		}
		if(haut != 0 && visited[i-1][j] != 1)
		{
			k = i - 1;
			while(lab[k][j] != 0 && visited[k][j] != 1)
			{
				visited[k][j] = 1;
				if(isHere(solve,lab[k][j], end))
				{
					for(distance = i-1; distance>=k ; distance--)
						lab[distance][j] = -1;
					i = k;
					break;
				}
				k = k - 1;
			}
			if(isHere(solve,lab[k][j], end))
				continue;
		}
		if(bas != 0 && visited[i+1][j] != 1)
		{
			k = i + 1;
			while(lab[k][j] != 0 && visited[k][j] != 1)
			{
				visited[k][j] = 1;
				if(isHere(solve,lab[k][j], end))
				{
					for(distance = i+1; distance<=k ; distance++)
						lab[distance][j] = -1;
					i = k;
					break;
				}
				k = k + 1;
			}
			if(isHere(solve,lab[k][j], end))
				continue;
    	}
    }
}