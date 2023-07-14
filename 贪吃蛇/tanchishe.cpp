#include <iostream>
#include <windows.h> 
#include<time.h>
#include<conio.h>
char dir = 1;//����
int snake_x[1005], snake_y[1005], snake_len, head = 2, score = 0;
int food_x, food_y;//ʳ�������

void gotoxy(int x, int y)  //�������ʾ����x,y������
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void gotoprint(int x, int y) {  //����Χǽ����ʽ
    gotoxy(x, y); printf("��");
}

void welcome()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // �����ı���ɫΪ��ɫ

    gotoxy(25, 6);  std::cout << "/**************************************************/" << std::endl;
    gotoxy(25, 8);  std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 10); std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 12); std::cout << "/\t\tWELCOME TO MY SNACK GANME          /" << std::endl;
    gotoxy(25, 14); std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 16); std::cout << "/\t\t\t\t\t\t   /" << std::endl;
    gotoxy(25, 18); std::cout << "/**************************************************/" << std::endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �ָ��ı���ɫΪĬ��ֵ

    system("pause");
    system("cls");//������������Ļ����
}
void setsnack() //��ʼ���������
{
    gotoprint(14, 15); gotoprint(14, 16); gotoprint(14, 17);
    snake_x[2] = 14; snake_y[2] = 15;//��ʼ���ߵ�����
    snake_x[1] = 14; snake_y[1] = 16;
    snake_x[0] = 14; snake_y[0] = 17;
}
void setgraph()
{
    for (int i = 0; i < 58; i += 2) //��ӡ���±߿�
    {
        gotoprint(i, 0); ////��ӡ��һ��
        gotoprint(i, 26);//��ӡ���һ��
     }
    for (int i=0; i < 28; i += 2)  //��ӡ���ұ߿�
    {
        gotoprint(0, i);///��ӡ��һ��
        gotoprint(56, i);//��ӡ���һ��
    }
    setsnack();//��ʼ���ߵ�����

 }

void createfood()
{
    while (1)
    {
        food_x = rand() % 25 + 1;//����
        food_y = rand() % 25 + 1;
        if (food_x % 2 != 0) food_x = food_x + 1;
        int flag=0;
        for (int i = head; i > head - snake_len; i--) //�ж�ʳ���������ߵ������Ƿ��غ�
        {
            if (snake_x[i] == food_x && snake_y[i] == food_y) flag = 1;
        }
        if (!flag) break;

    }
    gotoxy(food_x, food_y);
    std::cout << "��";
}
void gotodelete(int x, int y) {//���x,y���������
    gotoxy(x, y); printf("  ");
}
void running()
{
    int snake_len = 3, tx, ty;//��һ��������
    createfood();
    while (1) {
        if (_kbhit()) dir = _getch();//�Ӽ����ϻ�ȡ����
        if (dir == 'w') {//��
            tx = snake_x[head];
            ty = snake_y[head] - 1;
        }
        else if (dir == 's') {//��
            tx = snake_x[head];
            ty = snake_y[head] + 1;
        }
        else if (dir == 'a') {//��
            tx = snake_x[head] - 2;
            ty = snake_y[head];
        }
        else if (dir == 'd') {//��
            tx = snake_x[head] + 2;
            ty = snake_y[head];
        }
        else continue;//�������������ͣ
        if (tx < 1 || tx > 54 || ty < 1 || ty > 25) break;//�ﵽ�߽���˳�
        int judge = 0;			//�Ե��Լ����˳�
        for (int i = head - 1; i > head - snake_len; i--)
            if (snake_x[head] == snake_x[i] && snake_y[head] == snake_y[i]) judge = 1;
        if (judge) break;		//�Ե��Լ����˳�
        if (tx == food_x && ty == food_y) {
            score += 10; snake_len++; createfood();//�������ʳ��
        }
        else gotodelete(snake_x[head - snake_len + 1], snake_y[head - snake_len + 1]);
        head++;
        snake_x[head] = tx;
        snake_y[head] = ty;
        gotoprint(tx, ty); gotoxy(0, 27);//����������
        Sleep(200);//��ͣ200����
    }
    system("cls");//�����Ļ
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
