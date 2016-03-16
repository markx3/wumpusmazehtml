#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "pilhagenerica.h"

FILE *abreArquivo(void);
void comecaHtml(FILE *file);
void acabaHtml(FILE *file);
void mostraTitulo();
void mostraPosicoes(int sx,int sy,int ex,int ey);
void mostraCorrectPath(int ** correctPath,int lin,int col);
void mostraCheiro();
void mostraMaze(char **maze, int lin, int col, int score, int arrow);
void mostraArrow(int arrow);
void mostraEnd(int score);
void mostraBreeze();
void mostraGold();
void mostraDeadWumpus();
void mostraPilha(PilhaGenerica p, void(*mostra_info)(void*));
void mostraTile(void *value);
#endif /* _INTERFACE_H */