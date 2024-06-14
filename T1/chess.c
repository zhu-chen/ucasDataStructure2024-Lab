#include "chess.h"

int chessboard[8][8];
int HTry1[8]={-2,-1,1,2,2,1,-1,-2};
int HTry2[8]={1,2,2,1,-1,-2,-2,-1};

void jump_horse(corrdinate* a,corrdinate* b)//这个函数描述的是马每次的跳跃
{
    corrdinate temp;
    int i=0;
    if(count(*a)==0)
    {
        b->x=-1;
        b->y=-1;
        return;
    }
    int min=9;
    int ch;
    while(i<8)
    {
        
        if(a->visited[i]==1)
        {
            i++;
            continue;
        }
        int x=a->x+HTry1[i];
        int y=a->y+HTry2[i];
        if(x>=0&&x<8&&y>=0&&y<8&&chessboard[x][y]==0)
        {
            temp.x=x;
            temp.y=y;
            Initvisited(&temp);
            if(count(temp)<min)
            {
                min=count(temp);
                ch=i;
            }
            i++;
        }
        else
        {
            i++;        
        }
    }
    int x=a->x+HTry1[ch];
    int y=a->y+HTry2[ch];
    b->x=x;
    b->y=y;
    Initvisited(b);
    a->visited[ch]=1;
    return;
}

int main(){
    //TODO: ADD YOUR CODE HERE
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            chessboard[i][j]=0;
        }
    }
    Sqstack *S=(Sqstack*)malloc(sizeof(Sqstack));
    InitStack(S);
    corrdinate start,next;
    scanf("%d %d",&(start.x),&(start.y));
    Initvisited(&start);
    while(StackLength(*S)<63)
    {
        chessboard[start.x][start.y]=StackLength(*S)+1;
        jump_horse(&start,&next);
        while(next.x==-1)
        {
            chessboard[start.x][start.y]=0;
            pop(S,&start);
            if(StackLength(*S)==0&&count(start)==0)
            {
                printf("No Solution\n");
                return 0;
            }
            jump_horse(&start,&next);
        }
        push(S,start);
        start=next;
    }
    chessboard[start.x][start.y]=64;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            printf("%d ",chessboard[i][j]);
        }
        printf("\n");
    }
    //print_chessboard();
    return 0;
}

int count(corrdinate a)
{
    int count=0;
    for(int i=0;i<8;i++)
    {
        if(a.visited[i]==1)
        {
            continue;
        }
        int x=a.x+HTry1[i];
        int y=a.y+HTry2[i];
        if(x>=0&&x<8&&y>=0&&y<8&&chessboard[x][y]==0)
        {
            count++;
        }
    }
    return count;
}
int Initvisited(corrdinate *a)
{
    for(int i=0;i<8;i++)
    {
        a->visited[i]=0;
    }
    return 0;
}

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
int StackLength(Sqstack S)
{
    return S.top-S.base;
}
