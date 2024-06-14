#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

extern int chessboard[8][8];

void print_chessboard();

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define ERROR 0
#define OK 1
typedef char SElemType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}Sqstack;
int push(Sqstack *S ,SElemType e);
int pop(Sqstack *S,SElemType *e);
int InitStack(Sqstack *S);
int GetTop(Sqstack *S,SElemType *e);
