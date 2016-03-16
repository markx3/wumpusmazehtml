
#include <stdio.h>
#include <stdlib.h>
#include "labirinto.h"
#include "pilhagenerica.h"
#include "interface.h"

int play(Player *player, Wumpus *wumpus, char **maze, PilhaGenerica *pilha, int endX, int endY, int lin, int col) {
	Tile next;
	//char c;
	//int i;
	//system("clear");
	mostraTitulo();
	//printf("2016 @ UDESC\n> Marcos Felipe Eipper\n> Willian Kumlehmn\n> Elder Mariot\n> Matheus Valenza\n");
	getchar();
	//system("echo oi");
	while(player->x != endX &&
		  player->y != endY) {
		//system("clear");

		desempilha(pilha, &next);
		if(maze[next.x][next.y] == 'W') shoot_arrow(wumpus, player);
		if(maze[next.x][next.y] == 'F') mostraCheiro();//	// AQUI
		maze[player->x][player->y] = '.';
		player->x = next.x;
		player->y = next.y;
		if(maze[player->x][player->y] == 'G') pick_gold(player);
		check_trap(maze, player->x, player->y);
		maze[player->x][player->y] = '@';
			/*for(i = 0; i <= 7; i++) {
				printf("\n");
			}*/
		mostraMaze(maze, lin, col, player->score, player->arrow);
		//getchar();
		player->score = player->score - 1;
	}
	//system("clear");
	mostraMaze(maze, lin, col, player->score, player->arrow);
	mostraEnd(player->score);
	return TRUE;
}

int check_trap(char **maze, int i, int j) {
	int count = 0;
	for (count = -1; count <= 1; count++) {
		if (maze[i+1][j+count] == 'P') mostraBreeze();//printf("> Player: What a chilly breeze.\n");
	}
	for (count = -1; count <= 1; count++) {
		if (maze[i-1][j+count] == 'P') mostraBreeze();//printf("> Player: What a chilly breeze.\n");
	}
	if (maze[i][j-1] == 'P') mostraBreeze();//printf("> Player: What a chilly breeze.\n");
	if (maze[i][j+1] == 'P') mostraBreeze();//printf("> Player: What a chilly breeze.\n");
	return 1;
}

int pick_gold(Player *player) {
	player->score = player->score + 1000;
	mostraGold();
	return TRUE;
}

int shoot_arrow(Wumpus *wumpus, Player *player) {
	if (player->arrow == FALSE) return FALSE;
	player->arrow = FALSE;
	player->score = player->score - 10;
	wumpus->is_alive = FALSE;

	//
	mostraDeadWumpus();
	return TRUE;
}

int player_init(Player *player, char **maze, int i, int j) {
	player->is_alive = TRUE;
	player->arrow = TRUE;
	player->score = 0;
	player->x = i;
	player->y = j;
	maze[i][j] = '@';
	return TRUE;
}


int wumpus_init(Wumpus *wumpus, char **maze, int i, int j) {
	int count = 0;
	wumpus->x = i;
	wumpus->y = j;
	wumpus->is_alive = TRUE;
	for (count = -1; count <= 1; count++) {
		if (maze[i+1][j+count] != '#') maze[i+1][j+count] = 'F';
	}
	for (count = -1; count <= 1; count++) {
		if (maze[i-1][j+count] != '#') maze[i-1][j+count] = 'F';
	}
	if (maze[i][j-1] != '#') maze[i][j-1] = 'F';
	if (maze[i][j+1] != '#') maze[i][j+1] = 'F';
	return TRUE;
}


int recursiveSolve(int x, int y, char **maze, int **wasHere, int **correctPath, int endX, int endY, PilhaGenerica *pilha) {
	if (x == endX && y == endY) return 1; // Se encontrou a saida
	if (maze[x][y] == '#' || wasHere[x][y] || maze[x][y] == 'P') return 0; // Se voce esta numa parede ou ja esteve aqui
	wasHere[x][y] = 1;
	if (y != 0) { // Verifica se não está na lateral esquerda
		if (recursiveSolve(x, y-1, maze, wasHere, correctPath, endX, endY, pilha)) { // Chama a funçao um tile a esquerda
			Tile t;
			t.x = x; t.y = y;
			empilha(pilha, &t);
			correctPath[x][y] = 1; 	// Seta que o caminho pode ser percorrido
			return 1;
		}
	}
	if (y != 36) { // Verifica se nao está na lateral direita
		if (recursiveSolve(x, y+1, maze, wasHere, correctPath, endX, endY, pilha)) { // Chama função um tile a direita
			Tile t;
			t.x = x; t.y = y;
			empilha(pilha, &t);
			correctPath[x][y] = 1;
			return 1;
		}
	}
	if (x != 0) { // Verifica se não está na borda do topo
		if (recursiveSolve(x-1, y, maze, wasHere, correctPath, endX, endY, pilha)) { // Chama a função um tile para cima
			Tile t;
			t.x = x; t.y = y;
			empilha(pilha, &t);
			correctPath[x][y] = 1;
			return 1;
		}
	}
	if (x != 6) { // Verifica se não está na borda de baixo
		if (recursiveSolve(x+1, y, maze, wasHere, correctPath, endX, endY, pilha)) { // Chama a função um tile para baixo
			Tile t;
			t.x = x; t.y = y;
			empilha(pilha, &t);
			correctPath[x][y] = 1;
			return 1;
		}
	}
	return 0;
}

int **alloc_intMatrix(int i, int j) {
	int lin = i;
	int col = j;
	int **temp = NULL;
	temp = (int**)malloc(sizeof(int*)*i);
	for(i = 0; i <= lin; i++) {
		temp[i] = (int*)malloc(sizeof(int)*j);
	}
	for(i = 0; i < lin; i++) {
		for(j = 0; j < col; j++) {
			temp[i][j] = 0;
		}
	}
	return temp;
}

char **alloc_maze(int i, int j) {
	int lin = i;
	char **maze = NULL;
	maze = (char**)malloc(sizeof(char*)*i);
	for(i = 0; i <= lin; i++) {
		maze[i] = (char*)malloc(sizeof(char)*j);
	}
	return maze;
}

int load_maze(FILE file, char **maze, int lin, int col) {
	int i = 0, j = 0;
	for (i = 0; i <= lin; i++) {
		//printf("i = %d", i);
		for (j = 0; j <= col; j++) {
			//printf("j = %d", j);
			if(!fscanf(&file, "%c", &maze[i][j]))
				break;
			//printf("%c", maze[i][j]);
		}
	}
	printf("\n");
	return 1;
}

void pause_verbose(char *arg) {
	printf("%s", arg);
	//printf("> Press enter to continue.\n");
	getchar();
	system("clear");
}


void mostra_tile(void *value) {
	Tile *tile = value;
	int *x = &tile->x;
	int *y = &tile->y;
	printf("[%d, %d]\n", *x, *y);
}
