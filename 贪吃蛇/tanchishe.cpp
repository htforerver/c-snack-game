#include <iostream>
#include <windows.h> 
#include<time.h>
#include<conio.h>
char dir = 1;//方向
int snake_x[1005], snake_y[1005], snake_len, head = 2, score = 0;
int food_x, food_y;//食物的坐标

void gotoxy(int x, int y)  //将输出显示到（x,y）坐标
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void gotoprint(int x, int y) {  //设置围墙的样式
    gotoxy(x, y); printf("■");
}

void welcome()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // 设置文本颜色为红色

    gotoxy(25, 6);  std::cout << "/**************************************************/" << std::endl;
    gotoxy(25, 8);  std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 10); std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 12); std::cout << "/\t\tWELCOME TO MY SNACK GANME          /" << std::endl;
    gotoxy(25, 14); std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 16); std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 18); std::cout << "/**************************************************/" << std::endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 恢复文本颜色为默认值

    system("pause");
    system("cls");//按任意键清除屏幕内容
}
void setsnack() //初始化设的坐标
{
    gotoprint(14, 15); gotoprint(14, 16); gotoprint(14, 17);
    snake_x[2] = 14; snake_y[2] = 15;//初始化蛇的坐标
    snake_x[1] = 14; snake_y[1] = 16;
    snake_x[0] = 14; snake_y[0] = 17;
}
void setgraph()
{
    for (int i = 0; i < 58; i += 2) //打印上下边框
    {
        gotoprint(i, 0); ////打印第一行
        gotoprint(i, 26);//打印最后一行
     }
    for (int i=0; i < 28; i += 2)  //打印左右边框
    {
        gotoprint(0, i);///打印第一行
        gotoprint(56, i);//打印最后一行
    }
    setsnack();//初始化蛇的坐标

 }

void createfood()
{
    while (1)
    {
        food_x = rand() % 25 + 1;//控制
        food_y = rand() % 25 + 1;
        if (food_x % 2 != 0) food_x = food_x + 1;
        int flag=0;
        for (int i = head; i > head - snake_len; i--) //判断食物的坐标和蛇的坐标是否重合
        {
            if (snake_x[i] == food_x && snake_y[i] == food_y) flag = 1;
        }
        if (!flag) break;

    }
    gotoxy(food_x, food_y);
    std::cout << "⊙";
}
void gotodelete(int x, int y) {//清楚x,y坐标的内容
    gotoxy(x, y); printf("  ");
}
void running()
{
    int snake_len = 3, tx, ty;//下一步的坐标
    createfood();
    while (1) {
        if (_kbhit()) dir = _getch();//从键盘上获取按键
        if (dir == 'w') {//上
            tx = snake_x[head];
            ty = snake_y[head] - 1;
        }
        else if (dir == 's') {//下
            tx = snake_x[head];
            ty = snake_y[head] + 1;
        }
        else if (dir == 'a') {//左
            tx = snake_x[head] - 2;
            ty = snake_y[head];
        }
        else if (dir == 'd') {//右
            tx = snake_x[head] + 2;
            ty = snake_y[head];
        }
        else continue;//按其他任意键暂停
        if (tx < 1 || tx > 54 || ty < 1 || ty > 25) break;//达到边界就退出
        int judge = 0;			//吃到自己就退出
        for (int i = head - 1; i > head - snake_len; i--)
            if (snake_x[head] == snake_x[i] && snake_y[head] == snake_y[i]) judge = 1;
        if (judge) break;		//吃到自己就退出
        if (tx == food_x && ty == food_y) {
            score += 10; snake_len++; createfood();//重新随机食物
        }
        else gotodelete(snake_x[head - snake_len + 1], snake_y[head - snake_len + 1]);
        head++;
        snake_x[head] = tx;
        snake_y[head] = ty;
        gotoprint(tx, ty); gotoxy(0, 27);//消除光标干扰
        Sleep(200);//暂停200毫秒
    }
    system("cls");//清除屏幕
    gotoxy(40, 10); printf("Game Over!  Your Score is: %d\n", score);
    system("pause");
}

int main()
{
    welcome();
    setgraph();
    running();
    
    return 0;
    
}
