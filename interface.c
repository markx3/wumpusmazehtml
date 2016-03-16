#include <stdio.h>
#include "interface.h"
#include "pilhagenerica.h"
#include "labirinto.h"
#include <stdlib.h>

FILE *abreArquivo(void) {
	FILE *file;
	if(!(file = fopen("output.html", "a"))) exit(1);
	return file;
}

void comecaHtml(FILE *file) {
	fprintf(file, "<!DOCTYPE html>\n<head>Wumpus Maze<style>\np{font-family: monospace;}\n</style></head>\n<body>\n<p>\n");
	fclose(file);
}

void acabaHtml(FILE *file) {
	fprintf(file, "</p>\n</body>\n</html>");
	fclose(file);
}

void mostraPosicoes(int sx,int sy,int ex,int ey){
	FILE *file;
	file = abreArquivo();
	fprintf(file, "sX: %d | sY: %d\neX: %d | eY: %d<br>\n", sx, sy, ex, ey);
	fclose(file);
}

void mostraCorrectPath(int ** correctPath,int lin,int col){
	FILE *file;
	file = abreArquivo();
	int i = 0, j = 0;
	for (i =0; i <= lin; i++) {
		for (j = 0; j <= col; j++) {
			fprintf(file, "%d ", correctPath[i][j]);
		}
		fprintf(file, "<br>\n");
	}
	fclose(file);
}
void mostraCheiro() {
	FILE *file;
	file = abreArquivo();
	fprintf(file, "> Player: What is that disgusting smell?<br>\n");
	fclose(file);

}

void mostraMaze(char **maze, int lin, int col, int score, int arrow) {
	FILE *file;
	file = abreArquivo();
	int i = 0, j = 0;
	fprintf(file, "Wumpus Maze v1.0b         SCORE: %d<br>\n", score);
	for (i = 0; i <= lin; i++) {
		for (j = 0; j <= col; j++) {
			fprintf(file, "%c", maze[i][j]);
		}
		fprintf(file, "<br>");
	}
	fprintf(file, "<br>\n");
	mostraArrow(arrow);
	fclose(file);
}

void mostraTitulo(){
	system("figlet -c WUMPUS MAZE v1.0b | lolcat");
}

void mostraArrow(int arrow){
	FILE *file;
	file = abreArquivo();
	fprintf(file, "ARROWS: %d<br><br>\n\n", arrow);
	fclose(file);
}
void mostraEnd(int score) {
	FILE *file;
	file = abreArquivo();
	fprintf(file, "> Player: Finally I got out of this scary maze!<br>\n");
	fprintf(file, "> FINAL SCORE: %d<br>\n> Well done!<br>\n", score);
	fclose(file);
}
void mostraBreeze() {
	FILE *file;
	file = abreArquivo();
	fprintf(file, "> Player: What a chilly breeze.<br>\n");
	fclose(file);
}
void mostraGold() {
		FILE *file;
		file = abreArquivo();
		fprintf(file, "> Player: My luck is changing. This gold will be useful to kill that hideous Wumpus.<br>\n");
		fclose(file);
}

void mostraDeadWumpus() {
	FILE *file;
	file = abreArquivo();
	fprintf(file, "> Wumpus: AAAAAAWWW AWWWW NOOO I'M DEAD NOW WOOOOOOT<br>\n");
	fclose(file);
}

void mostraPilha(PilhaGenerica p, void(*mostra_info)(void*)) {
	FILE *file;
	file = abreArquivo();
	if (pilha_vazia(p)) return;
	int i = 0;
	fprintf(file, "Pile data:<br>\n");
	fclose(file);
	for (i = p.topo; i >= 0;i--) {
		mostra_info(p.dados[i]);
	}
	fclose(file);
}

void mostraTile(void *value) {
	FILE *file;
	file = abreArquivo();
	Tile *tile = value;
	int *x = &tile->x;
	int *y = &tile->y;
	fprintf(file, "[%d, %d]<br>\n", *x, *y);
	fclose(file);
}