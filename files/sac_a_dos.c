#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "hashtable.h"

/*

I :
Dans le pire des cas avec n éléments on peut avoir 2**n
Borne inférieure : 2**n

II:
On souhaite trouver la valeur de f(n,P)
f(1,d) = v0  si d>p0
         0   sinon

f(k+1,d) = max(vk+f(k,d-Pk) , f(k,d))  Si d >Pk
           f(k+1,d) = f(k,d) sinon

f(0,d) = 0 utilité dans les fonctions récursive ??? 

d<0
f(k,d) = -vk
*/
/* Création et destruction de matrice */

long max(long a, long b){
    if (a>b) {
        return a;
    }
    else {
        return b;
    }
}

long sac_rec(long* poids, long* valeurs, long n, long p){
    if (n<=0){
        return 0;
    }
    else if(p<0){
        return -valeurs[n];
    }
    else {
        return  max(valeurs[n-1]+sac_rec(poids,valeurs,n-1,p-poids[n-1]), sac_rec(poids,valeurs,n-1,p));
    }
}
//2 Omega de 2**n/2

/*


Si c'est pas optimale on a vu que ça se passait en omega de 2**n/2

On peut comparer plusieurs fois les mêmes pi et donc faire les mêmes calcul
*/


long** creer_matrice(long n1, long n2){
	long** mat = (long**)malloc(n1*sizeof(long*));
	for(long i=0; i<n1; i++){
		mat[i] = (long*)malloc(n2*sizeof(long));
	}
	return mat;
}

void del_matrice(long** mat, int n1){
	for(long i=0; i<n1; i++){
		free(mat[i]);
	}
	free(mat);
}

/* Génération d'instances aléatoires, et affichage d'instances */
void init_sad(long n, long p, long* poids, long* valeurs)
{
    long poids_div = p - 100;
    long vals_div = 100;
    long a = 7;
    long b = 11;
    for(long i=0;i<n;i++){
        a = a *7 % vals_div;
        b = b *11% poids_div;
        valeurs[i]  =  a + 1;
        poids[i] =  b + 1;
        assert(poids[i]<=p);
    }
}

long sac_asc(long* poids, long* valeurs, long n, long p){
    long** opt = creer_matrice(n+1,p+1);
    for (int i=0;i<n;i++){
        opt[i][0] = 0;
    }
    for (int i=0;i<p+1;i++){
        opt[0][i] = 0;
    }
    for(int i=1; i<n+1;i++){
        for(int j=1; j<p+1;j++){
            if(j-poids[i-1]>=0){
            opt[i][j]= max(opt[i-1][j],valeurs[i-1]+opt[i-1][j-poids[i-1]]); // a corriger !!!
            }else{
                opt[i][j] = opt[i-1][j];
            }
        }
    }
    return opt[n][p];
} // C'est mieux que les autres approches



bool* sac_asc_solution(long* poids, long* valeurs,long n, long p){
    long** opt = creer_matrice(n+1,p+1);
    for (int i=0;i<n+1;i++){
        opt[i][0] = 0;
    }
    for (int i=0;i<p+1;i++){
        opt[0][i] = 0;
    }
    for(int i=1; i<n+1;i++){
        for(int j=1; j<p+1;j++){
            opt[i][j]= max(opt[i-1][j-1],valeurs[i-1]+opt[i-1][j-poids[i-1]]);
        }
    }  // on mets tous a false puis on remonte la matrice en partant de en bas a droite
    bool* result = (bool*)(malloc((sizeof(bool))*(n+1)));
    for(int i = 0; i<n+1;i++){
            result[i]=false;
    }
    int x = n;
    int y = p;
    while (x>0 && y>0){
        result[x]= true;
        if (opt[x-1][y]>valeurs[x-1]+opt[x-1][y-poids[x-1]])
        {
            x=x-1;
        }
        else{
            x=x-1;
            y=y-poids[x];
        }
    }
    return result;
}


void print_sad(long n, long p, long* poids, long* valeurs){
    printf("Articles: %ld, pMax=%ld:\nProfits : ", n,p);
    for(long i=0;i<n;i++)
        printf("%ld ",valeurs[i]);
    printf("\nPoids : ");
    for(long i=0;i<n;i++)
        printf("%ld ",poids[i]);
    printf("\n");
}


int main(){
    long valeur[3] = {5,8,11}; 
    long poids[3] = {1,2,3};
    bool* oui = sac_asc_solution(valeur,poids,(long)3,(long)9);
    for(int i =0; i<3;i++){
        printf("%d",oui[i]);
        }
    printf("\n");
    printf("%ld",sac_asc(valeur,poids,3,1));
	return 0;
}
