#ifndef _LABIRINTO_H
#include "pilhagenerica.h"
#include "interface.h"
#define _LABIRINTO_H
#define TRUE 1
#define FALSE 0

typedef struct {
	int x;
	int y;
} Tile;

typedef struct {
	int x;
	int y;
	int is_alive;
} Wumpus;

typedef struct {
	int x;
	int y;
	int is_alive;
	int arrow;
	int score;
} Player;

int play(Player *player, Wumpus *wumpus, char **maze, PilhaGenerica *pilha, int endX, int endY, int lin, int col); // OK
int check_trap(char **maze, int i, int j); // OK
int pick_gold(Player *player); // OK
int shoot_arrow(Wumpus *wumpus, Player *player); // OK
int player_init(Player *player, char **maze, int i, int j); // OK
int wumpus_init(Wumpus *wumpus, char **maze, int i, int j); // OK
int load_maze(FILE file, char **maze, int lin, int col); // OK
int print_maze(char **maze, int lin, int col); // OK
char **alloc_maze(int i, int j); // OK
int **alloc_intMatrix(int i, int j); // OK
int recursiveSolve(int x, int y, char **maze, int **wasHere, int **correctPath, int endX, int endY, PilhaGenerica *pilha); // OK
void mostra_tile(void *value);
void pause_verbose(char arg[]);



#endif /* _LABIRINTO_H */