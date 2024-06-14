#include "chess.h"

int chessboard[8][8];

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

int main(){
    //TODO: ADD YOUR CODE HERE
    int x,y;
    scanf("%d %d",&x,&y);
    
    print_chessboard();
    return 0;
}