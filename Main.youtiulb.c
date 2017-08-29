#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH ""

typedef struct _node {
	char tipo;
	size_t qtde;
} STR;


void quickSort(STR  * vet, int ini, int fim) {
	int ph = ini, i, i2, k;
	STR * pt = vet;

	for (i = ini + 1; i <= fim; i++) {
		i2 = i;
		if (pt[i2].qtde < pt[ph].qtde) {
			k = pt[i2].qtde;
			while (i2 > ph) {
				pt[i2] = pt[i2 - 1];
				i2--;
			}
			pt[i2].qtde = k;
			ph++;
		}

		if (ph - 1 >= ini)
			quickSort(pt, ini, ph - 1);
		if (ph + 1 <= fim)
			quickSort(pt, ph + 1, fim);
	}
}


int main() {
	int * aparicoes = (int *) calloc(255 , sizeof(int));
	STR * liso;
	FILE * file = fopen(PATH, "rb");
	char * TESTE_STRING = "6AAAAAA 8BBBBBBBB 9CCCCCCCCC 3EEE 2KK 1A";
	int i = 0, j = 0, k = 0;

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
	}

	quickSort(liso, 0, j);
	printf("\n\nAFTER quicksort\n\n"); 
	for (i = 0; i < j; i++) {
		printf("tipo: %c, qtde: %d\n", liso[i].tipo, liso[i].qtde);
	}

	system("PAUSE");
	return 0;

}




