#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef int key_type;
typedef int value_type;

struct Node
{
  key_type key;
  value_type value;
  struct Node* left;
  struct Node* right;
};

typedef struct Node node;

struct BST {
  node* root;
};

typedef struct BST bst;

node* new_node(key_type k, value_type n){
  node* nouveau_noeud = (node*)(malloc(sizeof(node)));
  nouveau_noeud->key = k;
  nouveau_noeud->value = n;
  nouveau_noeud->left = NULL;
  nouveau_noeud->right = NULL;
  return nouveau_noeud;
}

bst bst_make_empty(){
  bst arbre = {NULL};
  return arbre;
}

void node_free(node* n){
  if (n->left!=NULL){
    node_free(n->left);
  }
  if (n->right!=NULL){
    node_free(n->right);
  }
  free(n);
}

/*
Si on ne libere pas tous les noeuds on va avoir une partie de la
memoire qui sera utiliser et au quel on ne pourra plus accéder on 
a donc une fuite de mémoire.
*/

void bst_free(bst* arbre){
  node_free(arbre->root);
  arbre->root = NULL;
}


node* node_set(node* t, key_type k, value_type v){
  if (t != NULL){
    if(k==t->key){
      t->value = v;
      return t;
    }
    else if(k>t->key){
      return node_set (t->right,k,v);
    } else {
      return node_set (t->left,k,v);
    }
  }
  else{
    node* nouveau = new_node(k,v);
    return nouveau;
  }

}

void bst_insert(bst* t, key_type k, value_type v){
  node_set(t->root,k,v);
}

bst bst_from_array(key_type key_arr[], value_type value_arr[], int n){
  bst arbre = bst_make_empty();
  for(int i = 0; i<n; i++){
    bst_insert(&arbre,key_arr[i],value_arr[i]);
  }
  return arbre;
}

bool node_get(node* t, key_type k, value_type* res){
  if(t->key!=k){
    if(t->key>k){
      if(t->left==NULL){
        return false;
      }
      else{
        return node_get(t->left,k,res);
      }
      
    } else if (t->right==NULL){
      return false;
    }
    else {
      node_get(t->right,k,res);
    }
  }else{
    *res = t->value;
    return true;
  }
}

bool bst_get(bst t, key_type k, value_type* res){
  return node_get(t.root,k,res);
}

void bst_print_couple(bst t, key_type k){
  value_type res = 0;
  if(bst_get(t,k,&res)){
    printf("key : %i    value : %i",k,res);
  }
  else {
    printf("c pats 2 dents");
  }
}

key_type node_key_min(node* n){
  if(n==NULL){
    assert(false);
  } else if(n->left!=NULL){
    node_key_min(n->left);
  } else{
    return n->key;
  }
}

key_type bst_min(bst t){
  node_key_min(t.root);
}

int node_size(node *n){
  if(n==NULL){
    return 0;
  }
  return 1 + node_size(n->left) + node_size(n->right); 
}

int bst_size(bst t){
  return node_size(t.root);
}

int max(int a,int b){
  if(a>b){
    return a;
  }
  return b;
}

int node_height (node *n){
  if(n==NULL){
    return -1;
  }
  if(n->right!=NULL && n->left!=NULL){
    return 1 + max((node_height(n->right)),(node_height(n->left)));
  }else if (n->right==NULL && n->left == NULL){
    return 1;
  } else if (n->right == NULL){
    return 1 + node_height(n->left);
  } else{
    return 1 + node_height(n->right);
  }
}

int bst_height(bst t){
  return node_height(t.root);
}

























//Ce squelette est uniquement utile pour le dernier exercice.

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int* random_array(int length){
	//crée un tableau de taille length contenant 0,...,length -1 dans un ordre aléatoire.
	//Ne pas oublier de libérer le tableau.
	int* res = (int*) malloc(length*sizeof(int));
	for(int i = 0; i<length; i++){
		res[i] = i;
	}
	shuffle(res, length);
}

int main(int argc, char** argv){

	return 0;
}