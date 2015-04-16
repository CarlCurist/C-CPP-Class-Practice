#include<cstdio>

char GameMap[100][100];
int n,m,startX,startY,endX,endY;

void move(char step)
{
    if('w'==step)
    {
        if(' '==GameMap[startX-1][startY])
        {
            GameMap[startX][startY]=' ';
            GameMap[--startX][startY]='H';
            goto leave;
        }
        if('O'==GameMap[startX-1][startY])
        {
            if('*'==GameMap[startX-2][startY])
                goto error;
            GameMap[startX][startY]=' ';
            GameMap[--startX][startY]='H';
            GameMap[startX-1][startY]='O';
        }
    }

    if('s'==step)
    {
        if(' '==GameMap[startX+1][startY])
        {
            GameMap[startX][startY]=' ';
            GameMap[++startX][startY]='H';
            goto leave;
        }
        if('O'==GameMap[startX+1][startY])
        {
            if('*'==GameMap[startX+2][startY])
                goto error;
            GameMap[startX][startY]=' ';
            GameMap[++startX][startY]='H';
            GameMap[startX+1][startY]='O';
        }
    }

    if('a'==step)
    {
        if(' '==GameMap[startX][startY-1])
        {
            GameMap[startX][startY]=' ';
            GameMap[startX][--startY]='H';
            goto leave;
        }
        if('O'==GameMap[startX][startY-1])
        {
            if('*'==GameMap[startX][startY-2])
                goto error;
            GameMap[startX][startY]=' ';
            GameMap[startX][--startY]='H';
            GameMap[startX][startY-1]='O';
        }
    }

    if('d'==step)
    {
        if(' '==GameMap[startX][startY+1])
        {
            GameMap[startX][startY]=' ';
            GameMap[startX][++startY]='H';
            goto leave;
        }
        if('O'==GameMap[startX][startY+1])
        {
            if('*'==GameMap[startX][startY+2])
                goto error;
            GameMap[startX][startY]=' ';
            GameMap[startX][++startY]='H';
            GameMap[startX][startY+1]='O';
        }
    }

    error:;
    printf("不能移动\n");

    leave:;
}
void PrintMap()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%c",GameMap[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main()
{
    char step;
    printf("推箱子游戏，请输入游戏棋盘的长宽\n");
    printf("请输入游戏地图，“*”表示障碍物，X表示目标，O表示箱子，H表示你现在所处的位子,请将地图边界用*封闭\n");
    printf("输入样例如下：\n6 6\n******\n*  H *\n*  O *\n*  * *\n* X  *\n******\n");
    scanf("%d %d",&n,&m);

    fflush(stdin);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%c",&GameMap[i][j]);
            if('H'==GameMap[i][j])
            {
                startX=i;
                startY=j;
            }
            if('X'==GameMap[i][j])
            {
                endX=i;
                endY=j;
            }
        }
       //fflush(stdin);
        getchar();//清空回车
        //getchar();
    }

    printf("输入wsad控制小人移动\n");

    while('O'!=GameMap[endX][endY])
    {
        scanf("%c",&step);
        move(step);
        PrintMap();
    }
    printf("Game Over\n");

    return 0;
}
