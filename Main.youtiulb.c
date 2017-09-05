
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH ""
#define COMPILE_OP 1
#define DECOMPILE_OP 2
#define OUTPUT_FLAG "-o"
#define INPUT_FLAG "-p"
#define COMPILE_FLAG "-c"
#define DECOMPILE_FLAG "-d"

typedef struct _node {
	char tipo;
	size_t qtde;
} STR;

//asd.exe -p caminho_conte -o cominhbo_saida -p

void quickSort(STR  * vet, int ini, int fim) {
	int ph = ini, i, i2;
	STR * pt = vet, k;

	for (i = ini + 1; i <= fim; i++) {
		i2 = i;
		if (pt[i2].qtde < pt[ph].qtde) {
			k = pt[i2];
			while (i2 > ph) {
				pt[i2] = pt[i2 - 1];
				i2--;
			}
			pt[i2]= k;
			ph++;
		}

		if (ph - 1 >= ini)
			quickSort(pt, ini, ph - 1);
		if (ph + 1 <= fim)
			quickSort(pt, ph + 1, fim);
	}
}

char * malloc_string(int size){
	char * res = (char * )malloc( (size + 1) * sizeof(char)) ;  //realloc
	res[strlen(res)] = '\0';
	return res;
	
}

int strequal(char * str1, char * str2){
	int i;
	for(i = 0; i < strlen(str1); i++)	
		if(str1[i] != str2[i])
			return 0;	
	return 1;
}

// char *argv[]    argv[i]                (vet[])   (vet)   (&vet[0])
int id_op(int argc, char ** argv, char src_path[], char out_path[]){
	int i;
	for(i = 1; i < argc; i++){
		if(strequal(argv[i], INPUT_FLAG)){
			//src_path = malloc_string(strlen(argv[i+ 1]) );
			strcpy(src_path, argv[i+1]);
			printf("O caminho de entrada e %s\n", src_path);
			//printf ("Endereco de src_path: %p ", &src_path);
		}else if(strequal(argv[i], OUTPUT_FLAG)){
			//out_path = malloc_string(strlen(argv[i+ 1] ) );
			strcpy(out_path, argv[i+1]);
			printf("O caminho de saida e %s\n", out_path);
		}else if(strequal(argv[i], COMPILE_FLAG)){
			return COMPILE_OP;
		}else if(strequal(argv[i], DECOMPILE_FLAG)){
			return DECOMPILE_OP;
		}
	}
	return -1;
	
}

int main(int argc, char ** argv) {
	int * aparicoes = (int *) calloc(255 , sizeof(int));
	STR * liso;
	FILE * file = fopen(PATH, "rb");
	char * TESTE_STRING = "6AAAAAA 8BBBBBBBB 9CCCCCCCCC 3EEE 2KK 1A";
	char src_path[100];// = NULL; // malloc 200
	char out_path[100];// = NULL;
	int i = 0, j = 0, k = 0;
	
	printf ("Endereco de src_path: %p ", &src_path);

	for (i = 0; i < strlen(TESTE_STRING); i++)
		aparicoes[TESTE_STRING[i]]++;


	for (i = 0; i < 255; i++)
		if (aparicoes[i] != 0)
			j++;

	liso = (STR * ) malloc(sizeof(STR) * j);
	if (liso == NULL)
		printf("ERRO NO MALLOC");
	for (i = 0; i < 256; i++) {
		if (aparicoes[i] != 0) {
			liso[k].tipo = (char) i;
			liso[k].qtde = aparicoes[i];
			k++;
		}
	}

	for (i = 0; i < j; i++) {
		printf("tipo: %c, qtde: %d\n", liso[i].tipo, liso[i].qtde);
	//	printf("erro");
	}

	quickSort(liso, 0, j);
	printf("\n\nAFTER quicksort\n\n");
	for (i = 0; i < j; i++) {

		printf("tipo: %c, qtde: %d\n", liso[i].tipo, liso[i].qtde);

	}
	
	printf("A saida foi %d, \n", 	id_op(argc, argv , src_path, out_path));

			printf("O caminho de entrada eh %s \n", src_path);
			printf("O caminho de saida eh %s \n", out_path);
	system("PAUSE");
	return 0;

}
