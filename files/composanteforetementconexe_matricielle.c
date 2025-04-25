#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Type de graphe orienté
// Les sommets sont des entiers de 0 à N-1
struct graphe {
  unsigned int N;
  bool** adj; // Matrice d'adjacence, représenté par un tableau 2D
};
typedef struct graphe graphe;

// Cherche si l'arête (s,t) existe
bool existe_arete(const graphe g, unsigned int s, unsigned int t) {
  return g.adj[s][t];
}

// Crée l'arête (s,t)
void modifier_arete(graphe *g, unsigned int s, unsigned int t, bool w) {
  g->adj[s][t] = w;
}

// Affichage du graphe
void afficher_graphe(const graphe g){

    // Affichage des arêtes
    for(unsigned int i = 0 ; i < g.N ; i++){
        for (unsigned int j = 0 ; j < g.N ; j++){
            if(existe_arete(g,i,j)){
                printf("%u -> %u\n",i,j);
            }
        }
    }
}

// Création d'un graphe à nb sommets, sans arête
graphe* init_graphe(unsigned int nb) {

  graphe* g = malloc(sizeof(graphe));
  g->N = nb;
  g->adj = malloc(nb * sizeof(bool*));

  // On n'a aucune arête initialement.
  for (unsigned int s = 0; s < nb; s++) {
  
    g->adj[s] = malloc(nb * sizeof(bool*));
    
    for (unsigned int t = 0; t < nb; t++) {
        modifier_arete(g,s,t,false);
    }
  }
  
  return g;
}

// Libération de la mémoire
void liberer_graphe(graphe *g) {
  for(unsigned int i = 0 ; i < g->N ; i++){
  	free(g->adj[i]);
  }
  free(g->adj);
  free(g);
}



//__________Partie I : Composantes fortement connexes : Approche matricielle__________

// Affiche la matrice de taille n x n donnée
void afficher_matrice(unsigned int n, bool** m1){
    for(unsigned int i = 0 ; i < n ; i++){
        for(unsigned int j = 0 ; j < n ; j++){
            if(m1[i][j]) printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}

// Alloue une matrice nulle taille n x n  ; complexité O(n^2)
bool** nulle(unsigned int n){
    bool** m = malloc(n * sizeof(bool*));
    
    for(unsigned int i = 0 ; i < n ; i++){
    	m[i] = malloc(n * sizeof(bool));
    }
    
    return m;
}

// Ecrit la matrice identité de taille n x n dans m1 ; complexité O(n^2)
bool** identite(unsigned int n){

    bool** m = nulle(n);
    
    for(unsigned int i = 0 ; i < n ; i++){
        	m[i][i] = true;
    }
    
    return m;
}

// Libère la mémoire d'une matrice de taille n x n ; complexité O(n)
void liberer_matrice(bool** m, int n){
	
	for(int i = 0 ; i < n ; i++){
		free(m[i]);
	}
	free(m);
}

void somme(unsigned int n, bool ** m1, bool** m2, bool** m3){
  for(int i =0; i<n;i++){
    for(int j = 0; j < n; j++){
      m3[i][j] = m1[i][j] || m2[i][j];
    }
  }
}

void produit(unsigned int n, bool ** m1, bool** m2, bool** m3){
  for(int i =0; i<n;i++){
    for(int j = 0; j < n; j++){
      for(int v =0; v<n; v++){
        m3[i][j] = m3[i][j] || (m1[i][v] && m2[v][j]);
      }
    }
  }
}

// Complexite en O(n^2) et O(n^3)

bool** chemins(const graphe g){
  bool** mat = g.adj;
  for(int i =0; i<g.N*g.N;i++){
    somme()
  }
  return mat;
}

// Complexite en O(n^4) 

unsigned int* cfc(const graphe g){
  int** tab = (int**)(malloc(sizeof(int*)*g.N));
  for(int i =0; i < g.N; i++){
    tab[i] = (int*)(malloc(sizeof(int)*g.N));
    for (int j = 0; j < g.N; j++){
      tab[i][j] = 0;
    }
  }
  

}

//__________Main__________
int main(int argc, char** argv) {
    
  graphe* g = init_graphe(8);
  
  modifier_arete(g,1,0,true);
  modifier_arete(g,0,4,true);
  modifier_arete(g,4,1,true);
  modifier_arete(g,5,4,true);
  modifier_arete(g,5,1,true);
  modifier_arete(g,5,6,true);
  modifier_arete(g,6,5,true);
  modifier_arete(g,6,2,true);
  modifier_arete(g,2,1,true);
  modifier_arete(g,3,2,true);
  modifier_arete(g,2,3,true);
  modifier_arete(g,7,3,true);
  modifier_arete(g,7,6,true);
  

  liberer_graphe(g);
  
  return 0;
}
