#ifndef _PILHA_H
#define _PILHA_H
#define ERRO_PILHA_VAZIA -1
#define ERRO_PILHA_CHEIA -2


typedef struct {
	void **dados;
	int topo;
	int capacidade;
	int tamInfo;
} PilhaGenerica;

int inicializa_pilha(PilhaGenerica *p, int c, int t);
int pilha_vazia(PilhaGenerica p);
int pilha_cheia(PilhaGenerica p);
int empilha(PilhaGenerica *p, void *info);
int desempilha(PilhaGenerica *p, void *info);
void mostra_pilha(PilhaGenerica p, void(*mostra_info)(void*));
void desaloca_pilha(PilhaGenerica *p); 

#endif /* _PILHA_H */