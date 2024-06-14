#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

extern int chessboard[8][8];

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int BOARD_SIZE = 8;
const int SQUARE_SIZE = SCREEN_WIDTH / BOARD_SIZE;

void printChessboard();

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
int InitStack(Sqstack *S)
{
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) 
    return ERROR;
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
int push(Sqstack *S,SElemType e)
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(SElemType*)realloc(S->base, (S->stacksize+ STACKINCREMENT )*sizeof(SElemType));
        if(!S->base)
        return ERROR;
    S->top=S->base+S->stacksize;
    S->stacksize+=STACKINCREMENT;
    }
    *(S->top++) =e; 
    return OK; 
}
int pop(Sqstack *S,SElemType *e)
{
    if(S->top==S->base)
    {
        return ERROR;
    }
    *e=*--(S->top);
    return OK;
}
int GetTop(Sqstack *S,SElemType *e)
{
    if(S->top==S->base)
    return ERROR;
    *e=*(S->top-1);
    return OK;
}