#include <iostream>
#include <windows.h> 
#include<time.h>
#include<conio.h>
#define HEIGHT  20  //设置地图高度
#define WIDTH   40  //设置地图宽度
#define PRINTF  printf("■");
#define LINE    printf("\n");
#define EMPTY   printf("  ");

typedef struct Snakebody
{
    int x, y;//身体的坐标
    struct Snakebody* next;//结构指针
}Snakebody;//先来创建保持身体的链表，贪吃蛇的核心代码就是该如何保存蛇的身体
typedef struct Snakexy
{
    int x;
    int y;
}Snakexy; //记录食物坐标
int sum = 0;     //计算得分
int JudgeSum = 0;    //判断是否加快
int Hard = 0;     //计算难度
int Pause = 200000000;   //暂停速度(移动速度)
int JudgeDirection = 4;   //判断方向
int* PJ = &JudgeDirection;  //用指针传值判断移动方向
Snakebody* Phead = NULL;  //存储着整个蛇身 不可更改
Snakebody* Phead_1 = NULL;  //指向蛇身
Snakebody* Pbady = NULL;  //创建节点
Snakebody* end = NULL;   //尾节点
Snakexy* Food = NULL;          //保存食物位置
void Front();                   //游戏开始页面1
void Jfood();     //检测是否吃到食物1
void Jwall();     //检测蛇头是否撞墙1
void Jsnake();     //检测蛇头是否撞到蛇身1
void ISnake();     //初始化蛇身1
void DeawMap();     //绘制地图1
void FoodRand();    //生成食物1
void ControlMove();    //控制移动和暂停1
void MoveCursor(int x, int y); //移动光标1
void Move();     //游戏运行1
void Showf();                   //显分数以及难度1
void Free();                    //释放内存
void gotoprint(int x, int y);
int main()
{
    Front();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);//绿
    DeawMap();
    Showf();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);// 暗白
    MoveCursor(34, 10);
    printf("↑");
    MoveCursor(31, 11);
    printf(" 使用←↓→来控制");
    MoveCursor(31, 12);
    printf("蛇的移动，撞墙游");
    MoveCursor(31, 13);
    printf("戏结束，每5分难度");
    MoveCursor(31, 14);
    printf("+1");
    ISnake();
    FoodRand();
    MoveCursor(40, 20);
    Move();
    return 0;
}
void Front()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // 设置文本颜色为红色

    MoveCursor(15, 6);  std::cout << "/**************************************************/" << std::endl;
    MoveCursor(15, 8);  std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 10); std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 12); std::cout << "/\t\tWELCOME TO MY SNACK GANME                /" << std::endl;
    MoveCursor(15, 14); std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 16); std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 18); std::cout << "/**************************************************/" << std::endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 恢复文本颜色为默认值

    system("pause");
    system("cls");//按任意键清除屏幕内容
}
void DeawMap()
{
    for (int i = 0; i <= WIDTH; i++)
    { //打印上边框
        gotoprint(i, 0);
    }
    for (int i = 0; i <= HEIGHT; i++) { //打印左右边框
        gotoprint(0, i);//
        gotoprint(HEIGHT + 10, i);//
        gotoprint(WIDTH, i);//
        for (int i = 0; i <= WIDTH; i++) { //打印下边框
            gotoprint(i, HEIGHT);
        }

    }
}
void MoveCursor(int x, int y)//设置光标位置(就是输出显示的开始位置)
{
    /*  COORD是Windows API中定义的一种结构体
    * typedef struct _COORD
    * {
    * SHORT X;
    * SHORT Y;
    * } COORD;
    *  */
    COORD pos = { x * 2,y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);//获得 标准输出的句柄   
    SetConsoleCursorPosition(output, pos); //设置控制台光标位置
}
void gotoprint(int x, int y) {
    MoveCursor(x, y); printf("■");
}
void FoodRand()
{
    srand((int)time(0));
    int x = rand() % 27 + 2;
    int y = rand() % 17 + 2;
    Phead_1 = Phead;
    for (int i = 0; i <= 200; i++)
    {
        if (Phead_1->x == x && Phead_1->y == y)
        {
            x = rand() % 27 + 2;
            y = rand() % 17 + 2;
        }
        else
        {
            Phead_1 = Phead_1->next;
        }
        if (Phead_1->next == NULL)
        {
            break;
        }
    }
    MoveCursor(x, y);
    PRINTF
        Food = (Snakexy*)malloc(sizeof(Snakexy));
    Food->x = x;
    Food->y = y;
    MoveCursor(33, 5);
    printf("  ");
    Showf();
    sum++;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);// 蓝
}
void ControlMove()
{
    if (GetAsyncKeyState(VK_UP) && 0x8000)
    {
        if (JudgeDirection == 2)
        {
        }
        else
        {
            JudgeDirection = 1;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) && 0x8000)
    {
        if (JudgeDirection == 1)
        {
        }
        else
        {
            JudgeDirection = 2;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) && 0x8000)
    {
        if (JudgeDirection == 3)
        {
        }
        else
        {
            JudgeDirection = 4;
        }
    }
    if (GetAsyncKeyState(VK_LEFT) && 0x8000)
    {
        if (JudgeDirection == 4)
        {
        }
        else
        {
            JudgeDirection = 3;
        }
    }
    if (GetAsyncKeyState(VK_RETURN) && 0x0D)
    {
        while (1)
        {
            if (GetAsyncKeyState(VK_RETURN) && 0x0D)
            {
                break;
            }
        }
    }
}
void ISnake()
{
    for (int i = 0; i < 5; i++)
    {
        Pbady = (Snakebody*)malloc(sizeof(Snakebody));
        Pbady->x = 5 - i;
        Pbady->y = 5;
        if (Phead == NULL)
        {
            Phead = Pbady;
        }
        else
        {
            end->next = Pbady;
        }
        Pbady->next = NULL;
        end = Pbady;
    }
    Phead_1 = Phead;
    while (Phead_1->next != NULL)
    {
        MoveCursor(Phead_1->x, Phead_1->y);
        PRINTF
            Phead_1 = Phead_1->next;
    }
}
void Move()
{
    while (1)
    {
        Phead_1 = Phead;
        while (Phead_1->next->next != NULL)
        {
            Phead_1 = Phead_1->next;
        }
        Phead_1->next = NULL;
        for (int i = 0; i < Pause; i++) {}
        ControlMove();
        MoveCursor(Phead_1->x, Phead_1->y);
        EMPTY
            //上面为消除尾部
            Snakebody* Phead_2 = (Snakebody*)malloc(sizeof(Snakebody));
        if (*PJ == 1)
        {
            Phead_2->x = Phead->x;
            Phead_2->y = Phead->y - 1;
        }
        if (*PJ == 2)
        {
            Phead_2->x = Phead->x;
            Phead_2->y = Phead->y + 1;
        }
        if (*PJ == 3)
        {
            Phead_2->x = Phead->x - 1;
            Phead_2->y = Phead->y;
        }
        if (*PJ == 4)
        {
            Phead_2->x = Phead->x + 1;
            Phead_2->y = Phead->y;
        }
        Phead_2->next = Phead;
        Phead = Phead_2;
        MoveCursor(Phead_2->x, Phead_2->y);
        PRINTF
            Jfood();
        Jwall();
        Jsnake();
        MoveCursor(40, 20);
    }
}
void Jfood()
{
    Phead_1 = Phead;
    if (Phead_1->x == Food->x && Phead_1->y == Food->y)
    {
        FoodRand();
        JudgeSum += 1;
        if (JudgeSum == 5)
        {
            JudgeSum = 0;
            Hard += 1;
            Pause -= 20000000;
        }
        while (Phead_1->next != NULL)
        {
            Phead_1 = Phead_1->next;
        }
        Snakebody* S = (Snakebody*)malloc(sizeof(Snakebody));
        S->x = Food->x;
        S->y = Food->y;
        S->next = NULL;
        Phead_1->next = S;
        ControlMove();
        MoveCursor(Phead_1->x, Phead_1->y);
        PRINTF
    }
    //获取食物的坐标和蛇头做对比
}
void Jwall()
{
    if (Phead->x == 0 || Phead->x == 29 || Phead->y == 0 || Phead->y == 19)
    {
        MoveCursor(11, 21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//设置红色
        printf("抱歉，你撞到了自己，游戏结束!              ");
        system("pause>nul");
        exit(0);
    }
}
void Jsnake()
{
    Phead_1 = Phead->next;
    while (Phead_1->next != NULL)
    {
        if ((Phead->x == Phead_1->x) && (Phead->y == Phead_1->y))
        {
            MoveCursor(11, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//设置红色
            printf("抱歉，你撞到了自己，游戏结束!          ");
            system("pause>nul");
            exit(0);
        }
        Phead_1 = Phead_1->next;
    }
}
void Showf()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);// 蓝
    MoveCursor(33, 5);
    printf("得分：%d", sum);
    MoveCursor(33, 6);
    printf("难度：%d", Hard);
}
void Free()
{
    while (Phead->next != NULL)
    {
        Phead = Phead->next;
        free(Phead);
    }
    free(Phead);
}
