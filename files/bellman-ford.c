#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#include <time.h>


struct graphe {
  int n; // Nombre de sommets
  int** adj; // Matrice d'adjacence, représenté par un tableau 1D
};
typedef struct graphe graphe;

// Renvoie un booléen indiquant si l'arête existe
bool existe_arete(const graphe g, int i, int j) {
  return (g.adj[i][j] > INT_MIN);
}

// Renvoie le poids de l'arête (i,j).
int poids_arete(const graphe g, int i, int j) {
  return g.adj[i][j];
}

// Crée l'arête (i,j) de capacité w
void modifier_arete(graphe *g, int i, int j, int w) {
  g->adj[i][j] = w;
}

// Crée l'arête (i,j) ET l'arête (j,i), de capacité w
void modifier_double_arete(graphe *g, int i, int j, int w) {
  g->adj[i][j] = w;
  g->adj[j][i] = w;
}


// Création d'un graphe à nb sommets
// que des arêtes de poids nul initialement
graphe* creer_graphe_vide(int nb) {

	// On alloue la mémoire pour g
	graphe* g = malloc(sizeof(graphe));
	g->n = nb;
	
	// On alloue et remplit la matrice d'adjacence
	g->adj = malloc(nb*sizeof(int*));
	for(int i = 0 ; i < nb ; i++){
        g->adj[i] = malloc(nb*sizeof(int));
		for(int j = 0 ; j < nb ; j++){
			modifier_arete(g,i,j,INT_MIN);
		}
	}
	
	return g;
}

// Libération de la mémoire
void liberer_graphe(graphe *g) {
    for(int i = 0 ; i < g->n ; i++){
        free(g->adj[i]);
	}
	free(g->adj);
	free(g);
}

// Affichage du graphe g
void afficher_graphe(const graphe g){

    // Affichage des arêtes
    for(int i = 0 ; i < g.n ; i++){
        for (int j = 0 ; j < g.n ; j++){
            if(existe_arete(g,i,j)){
                printf("%d -> %d, Poids : %d\n",i,j,poids_arete(g,i,j));
            }
        }
    }
}

int** init_chemins(const graphe g, int s)
{
  int ** mat = (malloc(g.n*sizeof(int*)));
  for(int i =0; i<g.n; i++){
    mat[i] = (malloc(g.n*sizeof(int)));
  }
  for(int i=0; i<g.n;i++){
    for(int j=0; j<g.n; j++){
      mat[i][j]=INT_MAX;
    }
  }
  mat[0][s]=0;
  return mat;
}

void calcul_chemins(const graphe g, int** p){
  for(int i =1;i<g.n;i++){
    for(int j=0;j<g.n;j++){
      int mini = p[i-1][j];
      for(int ouiii = 0 ; ouiii<g.n; ouiii++){
        if(existe_arete(g,ouiii,j) && mini != INT_MAX){
          if(mini>p[i-1][ouiii]+poids_arete(g,ouiii,j)){
            mini = p[i-1][ouiii]+poids_arete(g,ouiii,j);
          }
        }
      }
      p[i][j] = mini;
    }
  }
}

bool sans_cycle_negatif(const graphe g, int** p){
  bool result = true;
  for(int i=0; i<g.n; i++){
    for(int j =0; j<g.n; j++){
      if(existe_arete(g,i,j)){
        if(p[g.n-1][i]>p[g.n-1][j]+poids_arete(g,i,j)){
        result = false;
        printf("negatif");
        }
      }
    }
  }
  return result;
}

//__________Algorithme de Bellman-Ford__________

int* bellman_ford(const graphe g, int s){
  int** tab = init_chemins(g,s);
  calcul_chemins(g,tab);
  if(sans_cycle_negatif(g,tab)){
    return tab[g.n];
  }
  else{
    return NULL;
  }
}


//__________Main__________
int main(int argc, char** argv) {


  graphe* g = creer_graphe_vide(5);

  modifier_arete(g,0,1,6);
  modifier_arete(g,0,2,7);
  modifier_arete(g,1,2,8);
  modifier_arete(g,1,3,5);
  modifier_arete(g,1,4,-4);
  modifier_arete(g,2,3,-3);
  modifier_arete(g,2,4,9);
  modifier_arete(g,3,1,-2);
  modifier_arete(g,4,3,7);
  modifier_arete(g,4,0,2);

  afficher_graphe(*g);

  //__________Tests pour Bellman-Ford__________
  int ** p = init_chemins(*g,2);
  calcul_chemins(*g,p);
  if (sans_cycle_negatif(*g,p)){
    printf("a\n");
  }
  //printf("%d",bellman_ford(*g,2)[0]);

  liberer_graphe(g);
  
  return 0;
}