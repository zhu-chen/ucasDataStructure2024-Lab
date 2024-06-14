#include "chess.h"

int chessboard[8][8];
int HTry1[8]={-2,-1,1,2,2,1,-1,-2};
int HTry2[8]={1,2,2,1,-1,-2,-2,-1};

void jump_horse(corrdinate* a,corrdinate* b)//这个函数描述的是马每次的跳跃
{
    while(1)
    {
        if(a->visited>=8)
        {
            b->x=-1;
            b->y=-1;
            return;
        }
        int x=a->x+HTry1[a->visited];
        int y=a->y+HTry2[a->visited];
        if(x>=0&&x<8&&y>=0&&y<8&&chessboard[x][y]==0)
        {
            b->x=x;
            b->y=y;
            b->visited=0;
            a->visited++;
            return;
        }
        else
        {
            a->visited++;
            if(a->visited>=8)
            {
                b->x=-1;
                b->y=-1;
                return;
            }
        }
    }
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
    start.visited=0;
    while(StackLength(*S)<63)
    {
        chessboard[start.x][start.y]=StackLength(*S)+1;
        jump_horse(&start,&next);
        while(next.x==-1)
        {
            chessboard[start.x][start.y]=0;
            pop(S,&start);
            if(StackLength(*S)==0&&start.visited>=8)
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