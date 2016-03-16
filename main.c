#include <stdio.h>
#include <stdlib.h>
#include "labirinto.h"
#include "pilhagenerica.h"
#include "interface.h"


int main(int argc, char *argv[]) {
	if(argv[1] == NULL) {
		printf("> Warning: no maze file specified.\n");
		exit(EXIT_FAILURE);
	}
	comecaHtml(abreArquivo());
	PilhaGenerica pilha;
	inicializa_pilha(&pilha, 500, sizeof(Tile));

	Wumpus wumpus;
	Player player;
	int startX = 0, startY = 0, endX = 0, endY = 0;
	FILE *fp;
	int i = 0, j = 0;
	int lin = 0, col = 0;
	fp = fopen(argv[1], "r");
	if (fp == NULL) return EXIT_FAILURE;
	char c;
	while((c = getc(fp)) != EOF) {
		if (lin == 0) col++;
		if (c == '\n') lin++;
	}
	col--;
	rewind(fp);

	char **maze = NULL;
	maze = alloc_maze(lin, col);
	int **wasHere = NULL;
	int **correctPath = NULL;
	wasHere = alloc_intMatrix(lin, col);
	correctPath = alloc_intMatrix(lin, col);

	
	load_maze(*fp, maze, lin, col);
	for (i = 0; i <= lin; i++) {
		for (j = 0; j <= col; j++) {
			if(maze[i][j] == 'E') {
				endX = i; endY = j;
			}
			if(maze[i][j] == 'S') {
				startX = i; startY = j;
				player_init(&player, maze, i, j);
			}
			if(maze[i][j] == 'W') {
				//printf("Wumpus: [%d, %d]", i, j);
				wumpus_init(&wumpus, maze, i, j);
			}
		}
	}
		//printf("passed\n");
	mostraPosicoes(startX,startY,endX,endY);

	//pause_verbose("Detected coordinates.\n");
	fclose(fp);

	recursiveSolve(startX, startY, maze, wasHere, correctPath, endX, endY, &pilha);

	//print_maze(maze, lin, col);
	//pause_verbose("Current maze.\n");
	mostraCorrectPath(correctPath,lin,col);

	//pause_verbose("Matrix containing correct path to exit.\n");

	mostraPilha(pilha, mostraTile);
	//pause_verbose("Coordinates necessary to get to the exit.\n");
	play(&player, &wumpus, maze, &pilha, endX, endY, lin, col);
	acabaHtml(abreArquivo());

	return 0;
}
