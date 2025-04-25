#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



int puissance(int a, int n)
{
    if (n==1){
        return a%(n+1);
    }
    if (n%2==0){
        return (puissance(a*a, n/2))%(n+1);
    }
    else{
        return (a*puissance(a*a,(n-1)/2))%(n+1);
    }
}

bool fermat(int n){
    int aleatoire = rand()%n;
    if (aleatoire == 0) {
        aleatoire += 1;
    }
    return puissance(aleatoire%n, n-1)%n == 1 ;
}

bool fermat_amplifie(int n, int k){
    bool result = true;
    for (int i=0;i<k;i++){
        if((fermat(n))==false){
            result = false;
            break;
        }
    }
    return result;
}

bool est_premier(int n){
    for(int i = 2;i<n ; i++){
        if (n%i == 0){
            return false;
        } 
    }
    return true;
}

double proportions_erreurs(int n, int k, int p){
    bool premier = est_premier(n);
    double nb_true = 0;
    for(int i = 0; i<p;i++){
        if(fermat_amplifie(n, k)){
            nb_true += 1;
        }
    }
    printf("%f\n", nb_true);
    if(premier){
        return (1-(double)(nb_true)/p) *100;
    }
    else{
        return (double)((double)(p-nb_true)/((double)(p))) *100;
    }
}

int main(){
    srand(time(NULL));
    printf("%d", fermat_amplifie(7, 1));
    printf("\n");
    printf("%f\n", proportions_erreurs(561,1,10000));
    return 0;
}

void melange_knuth(int* tab, int n){
    for(int i =0; i<n ;i++){
        int aleatoire =rand()%n;
        int ancienne = tab[i];
        tab[i] = tab[aleatoire];
        tab[aleatoire] = ancienne;
    }
}
//O(n)
bool est_trie(int* tab, int n){
    for (int i=0;i<n-1; i++){
        if (tab[i+1]<tab[i]){
            return false;
        }
    }
    return true;
}

int tri_stupide(int* tab, int n){
    int nb_essais = 0;
    while(!(est_trie(tab))){
        melange_knuth(tab,n);
        nb_essais += 1;
    }
    return nb_essais;
}

//O(n!) en moyenne



