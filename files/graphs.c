#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>

struct sommet {
  unsigned int d; //debut
  unsigned int f; //fin
  unsigned int parent; //propre parent
  unsigned int etat;
} typedef sommet;

const unsigned int NONVU = 0;
const unsigned int EXPLORATION = 1;
const unsigned int VU = 2;

struct graphe {
  unsigned int N;
  sommet * S;
  bool* adj; // matrice d'adjacence
} typedef graphe;


//__________ Partie 1 : création de graphes orientés__________

int indice(unsigned int n, unsigned int i, unsigned int j){
  return n*i + j;
}

void modifier_arete(graphe *g, unsigned int s, unsigned int t, bool b)
{
  (g->adj)[indice(g->N,s,t)] = b;
}

bool existe_arete(graphe* g, unsigned int s, unsigned int t) 
{
  return (g->adj)[indice(g->N, s, t)];
}

graphe* init_graphe(unsigned int n)
{
  bool* adjacence = (bool*)malloc(n*n*n*n*sizeof(bool));
  for(int i=0;i<n*n*n*n;i++){
    adjacence[i] = false;
  }
  sommet* liste_s = (sommet*)malloc(n*n*sizeof(sommet));
  for(int i =0; i<n*n; i++){
    liste_s[i].d = NONVU;
    liste_s[i].f = VU;
    liste_s[i].parent = i;
    liste_s[i].etat = EXPLORATION;
  }
  graphe* resultat = (graphe*)malloc(sizeof(graphe));
  resultat->adj = adjacence;
  resultat->N = n*n;
  resultat->S = liste_s;
  //grille
  for(unsigned int i=0; i<n*n;i++)
  {
    for(unsigned int j=0; j<n*n;j++)
    {
      int x= i%n;
      int y= i/n;
      if (y<n-1){
        if(rand()%2==0){
          modifier_arete(resultat,indice(n*n,i,j),indice(n*n,i,j+1), true);
        }
        else{
          modifier_arete(resultat,indice(n*n,i,j+1),indice(n*n,i,j), true);
        }
      }
      if(x<n-1){
        if(rand()%2==0){
          modifier_arete(resultat, indice(n*n,i,j), indice(n*n,i+1,j),true);
        }
        else{
          modifier_arete(resultat, indice(n*n,i+1,j), indice(n*n,i,j),true);
        }
      }
    }
  }
  return resultat;
}

void liberer_graphe(graphe* g){
  printf("oui");
  free(g->adj);
  printf("ok");
  free(g->S);
  printf("non");
  free(g);
  printf("maybe");
}

void to_neato(const char* filename, const struct graphe g)
{
  unsigned int taille = sqrt(g.N);
  FILE * fichier = fopen(filename,'w');
  assert (fichier!=NULL);
  fprintf(fichier,"digraph G {\n");
  fprintf(fichier," node [shape = point colorsheme=paired12 width=0.4]\n");
  fprintf(fichier," edge [colorscheme=paired12 penwidth=4]\n");
  for(unsigned int i=0; i< g.N;i++){
    unsigned int x,y;
    x=i%taille;
    y=i/taille;
    fprintf(fichier, "%d[pos=\"%d,%d\"]",i,x,y);
    for(unsigned int j=0;j < g.N;j++){
      if(i !=j && existe_arete((&g),i,j)){
        fprintf(fichier," %d -> %d;\n",i,j);
      }
    }
  }
  fprintf(fichier,"}\n");
  fclose(fichier);
}


int main(int argc, char** argv) {
  srand(time(NULL));
  graphe* mon_graphe = init_graphe(5);

  //const char* nom = "test";
  //const graphe g=(*mon_graphe);
  //to_neato("test",g);
  printf("aaaaaaaa");
  liberer_graphe(mon_graphe);
  return 0;
}
