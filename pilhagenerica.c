#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcpy tá aqui //
#include "pilhagenerica.h"

int inicializa_pilha(PilhaGenerica *p, int c, int t) {
	if (!(p->dados = (void**)malloc(c*sizeof(void*))))exit(EXIT_FAILURE);
	p->topo = -1;
	p->capacidade = c;
	p->tamInfo = t;
	return 1;
}
int pilha_vazia(PilhaGenerica p) {
	return p.topo == -1;
}
int pilha_cheia(PilhaGenerica p) {
	return p.topo == p.capacidade-1;
}
int empilha(PilhaGenerica *p, void *info) {
	if (pilha_cheia(*p)) return ERRO_PILHA_CHEIA;
	p->topo++;
	if(!(p->dados[p->topo] = (void*)malloc(p->tamInfo)))exit(EXIT_FAILURE);
	memcpy(p->dados[p->topo], info, p->tamInfo);
	return 1;			// sucesso
}
int desempilha(PilhaGenerica *p, void *info) {
	if (pilha_vazia(*p)) return ERRO_PILHA_VAZIA;
	memcpy(info, p->dados[p->topo], p->tamInfo);
	free(p->dados[p->topo]);
	p->topo--;
	return 1;
}
void mostra_pilha(PilhaGenerica p, void(*mostra_info)(void*)) {
	if (pilha_vazia(p)) return;
	int i = 0;
	printf("Dados da pilha:\n");
	for (i = p.topo; i >= 0;i--) {
		mostra_info(p.dados[i]);
	}
}
void desaloca_pilha(PilhaGenerica *p) {
	int i = 0;
	for (i = 0; i <= p->topo; i++) {
		free(p->dados[i]);
	}
	free(p->dados);
}