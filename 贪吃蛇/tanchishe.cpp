#include <iostream>
#include <windows.h> 
#include<time.h>
#include<conio.h>
#define HEIGHT  20  //���õ�ͼ�߶�
#define WIDTH   40  //���õ�ͼ���
#define PRINTF  printf("��");
#define LINE    printf("\n");
#define EMPTY   printf("  ");

typedef struct Snakebody
{
    int x, y;//���������
    struct Snakebody* next;//�ṹָ��
}Snakebody;//���������������������̰���ߵĺ��Ĵ�����Ǹ���α����ߵ�����
typedef struct Snakexy
{
    int x;
    int y;
}Snakexy; //��¼ʳ������
int sum = 0;     //����÷�
int JudgeSum = 0;    //�ж��Ƿ�ӿ�
int Hard = 0;     //�����Ѷ�
int Pause = 200000000;   //��ͣ�ٶ�(�ƶ��ٶ�)
int JudgeDirection = 4;   //�жϷ���
int* PJ = &JudgeDirection;  //��ָ�봫ֵ�ж��ƶ�����
Snakebody* Phead = NULL;  //�洢���������� ���ɸ���
Snakebody* Phead_1 = NULL;  //ָ������
Snakebody* Pbady = NULL;  //�����ڵ�
Snakebody* end = NULL;   //β�ڵ�
Snakexy* Food = NULL;          //����ʳ��λ��
void Front();                   //��Ϸ��ʼҳ��1
void Jfood();     //����Ƿ�Ե�ʳ��1
void Jwall();     //�����ͷ�Ƿ�ײǽ1
void Jsnake();     //�����ͷ�Ƿ�ײ������1
void ISnake();     //��ʼ������1
void DeawMap();     //���Ƶ�ͼ1
void FoodRand();    //����ʳ��1
void ControlMove();    //�����ƶ�����ͣ1
void MoveCursor(int x, int y); //�ƶ����1
void Move();     //��Ϸ����1
void Showf();                   //�Է����Լ��Ѷ�1
void Free();                    //�ͷ��ڴ�
void gotoprint(int x, int y);
int main()
{
    Front();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);//��
    DeawMap();
    Showf();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);// ����
    MoveCursor(34, 10);
    printf("��");
    MoveCursor(31, 11);
    printf(" ʹ�á�����������");
    MoveCursor(31, 12);
    printf("�ߵ��ƶ���ײǽ��");
    MoveCursor(31, 13);
    printf("Ϸ������ÿ5���Ѷ�");
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // �����ı���ɫΪ��ɫ

    MoveCursor(15, 6);  std::cout << "/**************************************************/" << std::endl;
    MoveCursor(15, 8);  std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 10); std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 12); std::cout << "/\t\tWELCOME TO MY SNACK GANME                /" << std::endl;
    MoveCursor(15, 14); std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 16); std::cout << "/\t\t\t\t\t\t         /" << std::endl;
    MoveCursor(15, 18); std::cout << "/**************************************************/" << std::endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �ָ��ı���ɫΪĬ��ֵ

    system("pause");
    system("cls");//������������Ļ����
}
void DeawMap()
{
    for (int i = 0; i <= WIDTH; i++)
    { //��ӡ�ϱ߿�
        gotoprint(i, 0);
    }
    for (int i = 0; i <= HEIGHT; i++) { //��ӡ���ұ߿�
        gotoprint(0, i);//
        gotoprint(HEIGHT + 10, i);//
        gotoprint(WIDTH, i);//
        for (int i = 0; i <= WIDTH; i++) { //��ӡ�±߿�
            gotoprint(i, HEIGHT);
        }

    }
}
void MoveCursor(int x, int y)//���ù��λ��(���������ʾ�Ŀ�ʼλ��)
{
    /*  COORD��Windows API�ж����һ�ֽṹ��
    * typedef struct _COORD
    * {
    * SHORT X;
    * SHORT Y;
    * } COORD;
    *  */
    COORD pos = { x * 2,y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);//��� ��׼����ľ��   
    SetConsoleCursorPosition(output, pos); //���ÿ���̨���λ��
}
void gotoprint(int x, int y) {
    MoveCursor(x, y); printf("��");
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
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);// ��
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
            //����Ϊ����β��
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
    //��ȡʳ����������ͷ���Ա�
}
void Jwall()
{
    if (Phead->x == 0 || Phead->x == 29 || Phead->y == 0 || Phead->y == 19)
    {
        MoveCursor(11, 21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//���ú�ɫ
        printf("��Ǹ����ײ�����Լ�����Ϸ����!              ");
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//���ú�ɫ
            printf("��Ǹ����ײ�����Լ�����Ϸ����!          ");
            system("pause>nul");
            exit(0);
        }
        Phead_1 = Phead_1->next;
    }
}
void Showf()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);// ��
    MoveCursor(33, 5);
    printf("�÷֣�%d", sum);
    MoveCursor(33, 6);
    printf("�Ѷȣ�%d", Hard);
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
