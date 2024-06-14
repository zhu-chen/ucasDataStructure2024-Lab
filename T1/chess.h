#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

extern int chessboard[8][8];

void print_chessboard();

#ifndef TEST
#define TEST 1
#define STACK_INIT_SIZE 10000
#define STACKINCREMENT 1000
#define ERROR 0
#define OK 1
#endif

typedef struct corrrdinate{
    int x;
    int y;
    int visited;
}corrdinate;
typedef corrdinate SElemType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}Sqstack;
int push(Sqstack *S ,SElemType e);
int pop(Sqstack *S,SElemType *e);
int InitStack(Sqstack *S);
int GetTop(Sqstack *S,SElemType *e);
int StackLength(Sqstack S);