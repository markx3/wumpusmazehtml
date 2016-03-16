#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include "labirinto.h"
#include "pilhagenerica.h"

#include <stdio.h>  // for printf

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }


/************* Test case functions ****************/

void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

void pileInit_test(void) {
  PilhaGenerica pilha;
  CU_ASSERT_EQUAL( inicializa_pilha(&pilha, 500, sizeof(Tile)), TRUE);
}

void allocMaze_test(void) {
  char **maze;
  CU_ASSERT_EQUAL( (maze = alloc_maze(1, 1)), maze);
}

void loadMaze_test(void) {
  char **maze;
  maze = alloc_maze(7, 37);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  CU_ASSERT_EQUAL( (load_maze(*fp, maze)), TRUE);
}

void printMaze_test(void) {
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  CU_ASSERT_EQUAL( (print_maze(maze, 7, 37)), TRUE);
}

void alloc_intMatrix_test(void) {
  int **test = NULL;
  CU_ASSERT_EQUAL( (test = alloc_intMatrix(5, 5)), test);
}

void player_init_test(void) {
  Player player;
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  CU_ASSERT_EQUAL( (player_init(&player, maze, 6, 1)), TRUE);
}

void wumpus_init_test(void) {
  Wumpus wumpus;
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  CU_ASSERT_EQUAL( (wumpus_init(&wumpus, maze, 4, 29)), TRUE);
}

void shoot_arrow_test(void) {
  Player player;
  Wumpus wumpus;
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  player_init(&player, maze, 6, 1);
  wumpus_init(&wumpus, maze, 4, 29);
  CU_ASSERT_EQUAL( (shoot_arrow(&wumpus, &player)), TRUE);
}

void pick_gold_test(void) {
  Player player;
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r")));
  load_maze(*fp, maze);
  player_init(&player, maze, 6, 1);
  CU_ASSERT_EQUAL( (pick_gold(&player)), TRUE);
}

void check_trap_test(void) {
  //4, 11
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  CU_ASSERT_EQUAL( (check_trap(maze, 4, 11)), TRUE);
}

void recursiveSolve_test(void) {
  PilhaGenerica pilha;
  inicializa_pilha(&pilha, 500, sizeof(Tile));
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  int **wasHere = NULL;
  int **correctPath = NULL;
  wasHere = alloc_intMatrix(7, 36);
  correctPath = alloc_intMatrix(7, 36);
  CU_ASSERT_EQUAL( (recursiveSolve(6, 1, maze, wasHere, correctPath, 0, 33, &pilha)), TRUE);
}

void play_test(void) {
  PilhaGenerica pilha;
  Player player;
  Wumpus wumpus;
  inicializa_pilha(&pilha, 500, sizeof(Tile));
  char **maze;
  maze = alloc_maze(7, 36);
  FILE *fp = NULL;
  if(!(fp = fopen("maze.txt", "r"))) exit(1);
  load_maze(*fp, maze);
  int **wasHere = NULL;
  int **correctPath = NULL;
  wasHere = alloc_intMatrix(7, 36);
  correctPath = alloc_intMatrix(7, 36);
  recursiveSolve(6, 1, maze, wasHere, correctPath, 0, 33, &pilha);
  player_init(&player, maze, 6, 1);
  wumpus_init(&wumpus, maze, 4, 29);
  CU_ASSERT_EQUAL( (play(&player, &wumpus, maze, &pilha, 0, 33, 7, 37)), TRUE);
}
/************* Test Runner Code goes here **************/

int main ( void )
{

   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "wumpus_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "pileInit_test", pileInit_test))               ||
        (NULL == CU_add_test(pSuite, "allocMaze_test", allocMaze_test))             ||
        (NULL == CU_add_test(pSuite, "loadMaze_test", loadMaze_test))               ||
        (NULL == CU_add_test(pSuite, "printMaze_test", printMaze_test))             ||
        (NULL == CU_add_test(pSuite, "alloc_intMatrix_test", alloc_intMatrix_test)) ||
        (NULL == CU_add_test(pSuite, "player_init_test", player_init_test))         ||
        (NULL == CU_add_test(pSuite, "wumpus_init_test", wumpus_init_test))         ||
        (NULL == CU_add_test(pSuite, "shoot_arrow_test", shoot_arrow_test))         ||
        (NULL == CU_add_test(pSuite, "pick_gold_test", pick_gold_test))             ||
        (NULL == CU_add_test(pSuite, "check_trap_test", check_trap_test))           ||
        (NULL == CU_add_test(pSuite, "recursiveSolve_test", recursiveSolve_test))   ||
        (NULL == CU_add_test(pSuite, "play_test", play_test))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
