#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


int MAX_CAPACITY = 1048576; // 2^20

struct tas {
int * tab ;
int taille ;
};

typedef struct tas tas ;

tas nouveau_tas(){
    int* tab = (int*)(malloc(MAX_CAPACITY));
    tas t = {tab, 0};
    return t;
}

void detruire_tas(tas t){
    free(t.tab);
}

bool prop_locale(tas t, int i){
    if (t.taille>=2*i+1){
    if (t.tab[2*i+1]<= t.tab[i] && t.tab[2*i+2]<= t.tab[i]){
        return true;
    }
    } else if (t.taille==2*i){
        if (t.tab[2*i+1]<= t.tab[i]){
            return true;
        }
    } else return true;
    return false;
}

bool est_tas(tas t){
    for (int i =0; i< t.taille;i++){
        if(prop_locale(t,i)==false){
            return false;
        }
    }
    return true;
}

void swap(tas t, int i, int j){
    if(i<t.taille && j< t.taille){
        int temp = t.tab[i];
        t.tab[i]=t.tab[j];
        t.tab[j]=temp;
    }
}

int parent(int i){
    return (i-1)/2;
}

int tamiser(tas t, int i){
    while(i!=0 && t.tab[i]>parent(i)){
        swap(t,i,parent(i));
        i=parent(i);
    }
    return i;
}

void tasser(tas t, int i){
    int max;
    while(2*i+1<t.taille && (t.tab[i]<t.tab[2*i+1] || t.tab[i]<t.tab[2*i+2])){
        if(t.tab[2*i+1]>t.tab[2*i+2]){
            max = 2*i+1;
        }else{
            max = 2*i+2;
        }
        if(t.taille == 2*i+1){
            swap(t,i,2*i+1);
            i=2*i+1;
        }else{
            swap(t,i,max);
            i=max;
        }
    }
}

//les parents du noeudajouter peut violer la proprité locale du tas
//on peut tasser l'élément ajouter

void ajouter(tas* t, int etiquette){
    t->tab[t->taille] = etiquette;
    t->taille += 1;
    tasser(*t, t->taille-1);
}

// la racine eput violer la propriete locale du tat
// on peut tamiser

int retirer_racine(tas* t){
    swap(*t,0,t->taille-1);
    t->taille -= 1;
    tamiser(*t,0);
    return t->tab[t->taille];
}

void retirer_noeud(tas* t, int i){
    swap(*t, i, t->taille-1);
    t->taille-=1;
    i = tamiser(*t, i);
    tasser(*t, i);
}

tas tableau_to_tas(int* tableau, int n){
    tas t = nouveau_tas();
    for(int i =0; i<n; i++){
        ajouter(&t, tableau[i]);
    }
    return t;
}

void vider_dans_tableau(tas* t, int* tableau){
    for(int i = t->taille -1; i>=0; i--){
        tableau[i]=t->tab[t->taille-1-i];
    }
}

void tri_par_tas(int* tableau, int n){ //O(nlog(n))
    tas t = tableau_to_tas(tableau, n);
    vider_dans_tableau(&t, tableau);
}

/*
I : ≪ tab[k, n] est trié et contient les n - k plus grands éléments du tableau initial. ≫
En entrant dans la boucle k=0 et tab est un tableau trié de taille n donc un tableau trié de taille n - k
Supposons que I est vraie a j et montrons qu'il reste vraie à l'étape j+1.
≪ tab[j, n] est trié et contient les n - j plus grands éléments du tableau initial. ≫
puis on enlève l'élement j du tableau tab de vient tab[j+1,n] et reste donc trié car tab[j+1,n] est une partie de tab[j,n] qui était trié.


Ceux qui fonctionne sont tamiser de 0 à n-1 
et tasser de n-1 à 0 
or la complexité de tasser de n-1 a 0 est en O(n) car a chaque fois que l'on tasse un Noeud(g,x,d) on a que g est tasser et d est tasser donc on va faire N échange au max soit
O(n) la ou l'autre est en O(nlog(n)
*/


int main(){
    return 0;
}