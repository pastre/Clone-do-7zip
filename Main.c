#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
    char data;
    int peso;
    struct _node * esq;
    struct _node * dir;
}NODE;

typedef struct _element{
    NODE * node;
    struct _element * prox;
}ELEMENT;


NODE * new_node(char  data, int peso, NODE * esq, NODE * dir){
    NODE * res = (NODE * ) malloc(sizeof(NODE));
    res -> data = data;
    res -> peso = peso;
    res -> esq = esq;
    res -> dir = dir;

    return res;
}

ELEMENT  * init_alfabeto(char * stream, int * len, ELEMENT * * ancora, int index){
	int * aparicoes = (int *) calloc(255 , sizeof(int));
	//printf("NEW LOOP, Index: %d\n", index);
    int i, j = 0, k = 0;
    ELEMENT * res;
    NODE * res_node;
	for (i = 0; i < strlen(stream); i++)
		aparicoes[stream[i]]++;

	for (i = 0; i < 255; i++)
		if (aparicoes[i] != 0)
			(*len)++;
        else
            aparicoes[i] == 0;

    res = (ELEMENT * ) malloc(sizeof(ELEMENT) );

    do{
       // printf("Index: %d\n ", index);
        index++;
        if(index >= 256)
            return ancora;
    }while(aparicoes[index] == 0);

    res -> node = new_node( (char) index, aparicoes[index], NULL, NULL);

    //printf("Adicionado NODE com data %c e peso %d\n", res -> node -> data, res -> node -> peso);
    res ->prox = *ancora;
    *ancora = res;

    return init_alfabeto(stream, len, ancora, index);
}

//Inicia a lista encadeada
void init_list(ELEMENT * * ancora){
    * ancora = NULL;
}

//Imprime a lsita encadeada
void prt(ELEMENT * res){

    char  c = (res -> node -> data);
    printf("C: %c, P: %d\n", c, res -> node -> peso);
    if(res ->prox != NULL)
    prt(res -> prox);
}

//MergeSort do stackOverflow
ELEMENT *sort(ELEMENT *lst) {
    if (!lst || !lst-> prox)
         return lst;
   ELEMENT *q = lst, *p = lst-> prox-> prox;
  while (p && p-> prox) {
    q = q-> prox;
    p = p-> prox-> prox;
  }
   ELEMENT *mid = q-> prox;
  q-> prox = NULL;
   ELEMENT *fst = sort(lst), *snd = sort(mid);
   ELEMENT rtn[1], *tail = rtn;
  while (fst && snd) {
    if (fst->node -> peso < snd->node -> peso) {
      tail-> prox = fst;
      tail = fst;
      fst = fst-> prox;
    } else {
      tail-> prox = snd;
      tail = snd;
      snd = snd-> prox;
    }
  }
  while (fst) {
    tail-> prox = fst;
    tail = fst;
    fst = fst-> prox;
  }
  while (snd) {
    tail-> prox = snd;
    tail = snd;
    snd = snd-> prox;
  }
  tail-> prox = NULL;
  return rtn-> prox;
}


NODE * init_tree(ELEMENT * ancora){
    int peso_res = ancora ->prox->node->peso + ancora->node->peso;

        NODE * nNode = new_node(NULL, peso_res, ancora ->prox->node, ancora->node);
        ancora -> prox -> node = nNode;
        //deleteNode(ancora);
        ancora = ancora -> prox;
        printf("->Novo alfabeto: \n");
        ancora = sort(ancora);
        prt(ancora);
        if(ancora -> prox == NULL)
            return ancora->node;
    return(init_tree(ancora));
}

//Funcao pra printar arvore do stackoverflow
void print2DUtil(NODE *root, int space)
{
    int i;
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->dir, space);

    // Print current node after space
    // count
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("C: %c P: %d\n", root->data, root -> peso);

    // Process left child
    print2DUtil(root->esq, space);
}

int main(){
    ELEMENT * alfabeto;
    NODE * raiz;
	char * TESTE_STRING = "6AAAAAA 8BBBBBBBB 9CCCCCCCCC 3EEE 2KK 1A";
    int lenght = 0;
    init_list(&alfabeto);
    init_alfabeto(TESTE_STRING, &lenght, &alfabeto, 0);
   // prt(alfabeto);
    printf("Sorted: \n");
    alfabeto=sort(alfabeto);
    prt(alfabeto);
    //deleteNode(&alfabeto, 2);
   // printf("A\n");
    //prt(alfabeto);
    raiz = init_tree(alfabeto);

  //  Tree_inOrder(raiz);

  printf("2D: \n");
  print2DUtil(raiz, 0);
}

