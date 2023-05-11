#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

using namespace std;

bool gameOver;
const int width = 35;   // map width
const int heigth = 20;  // map heigth

const int InfWidth = 30; // the width of the table
const int countROW = 6; // number of lines
const int InfX = 55, infY = 3;     //coordinates board information

int x, y, fruitX, fruitY, score;  //coordinates of the head and fruit

int nTail; // кількість сигментів змії
int TailX[100], TailY[100];

enum mDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; // possible directions of movement
mDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    score = 0;

    x = width / 2;
    y = heigth / 2;

    fruitX = rand() % width;
    fruitY = rand() % heigth;
}

void DrawInfGame()
{

    COORD c{InfX, infY};

    for (int row = 0; row < (countROW * 2) + 1; row++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
         
        if (!(row & 1))  // друк пробілів між рядками
        { 
            for (int i = 0; i < InfWidth + 1; i++)
                (i == 0) || (i == InfWidth) ? cout << "." : cout << "-";
        }
        else if(row == 1)
            cout << "|" << setw(InfWidth / 2) << "SNAKE" << setw(InfWidth / 2) << "|";

        else if(row == 3)
            cout << "|" << setw(InfWidth / 2.5) << "SCORE:" << setw(InfWidth / 2.5) << score << setw(InfWidth / 5) << "|";

        else if (row == 5)
            cout << "|" << setw(InfWidth / 2) << "CONTROL" << setw(InfWidth / 2) << "|";

        else if (row == 7)
            cout << "|" << setw(InfWidth / 3) << "LEFT(a)" << setw(InfWidth / 6) << "|" << setw(InfWidth / 3) << "RIGHT(d)" << setw(InfWidth / 6) << "|";

        else if (row == 9)
            cout << "|" << setw(InfWidth / 3) << "UP(w)" << setw(InfWidth / 6) << "|" << setw(InfWidth / 3) << "DOWN(s)" << setw(InfWidth / 6) << "|";

        else if (row == 11)
            cout << "|" << setw(InfWidth / 2) << "EXIT(X)" << setw(InfWidth / 2) << "|";
        c.Y++; // перехід на рядок вниз
    }
}

void DrawScore()
{
    COORD c{ InfX, infY  + 3}; // Це відповідні координати в таблиці на екрані 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    cout << "|" << setw(InfWidth / 2.5) << "SCORE:" << setw(InfWidth / 2.5) << score << setw(InfWidth / 5) << "|";


}

void DrawMap()
{
    //system("cls");
    DrawScore();

    COORD c;
    c.X = 0;
    c.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < heigth; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) cout << "#";

            if (i == y && j == x)
            {
                SetConsoleTextAttribute(col, 1);
                cout << "0";
                SetConsoleTextAttribute(col, 15);
            }
            
            else if (i == fruitY && j == fruitX)
            {
                SetConsoleTextAttribute(col, 2);
                cout << "F";
                SetConsoleTextAttribute(col, 15);
            }
        
            else
            {
                bool print = false;

                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                    {
                        SetConsoleTextAttribute(col, 1);
                        cout << "o";
                        SetConsoleTextAttribute(col, 15);
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }

            if (j == width - 1) cout << "#";

        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a': dir = LEFT; break;

        case 'd': dir = RIGHT; break;

        case 'w': dir = UP; break;

        case 's': dir = DOWN; break;

        case 'x': gameOver = true; break;
        }
    }
}

void Logic()
{
    int prevX = TailX[0];
    int prevY = TailY[0];

    TailX[0] = x;
    TailY[0] = y;

    int prev2X, prev2Y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];

        TailX[i] = prevX;
        TailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }


    switch (dir)
    {
    case LEFT: x--; break;

    case RIGHT: x++;  break;

    case UP: y--; break;

    case DOWN: y++; break;
    }

    if (x >= width || y >= heigth || x < 0 || y < 0) // перевірка на удар об стіну
        gameOver = true;

    for (int i = 0; i < nTail; i++) // перевірка на удар об хвіст
    {
        if (TailX[i] == x && TailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY)
    {
        
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % heigth;
        nTail++;
    }
}

int main()
{
    Setup();
    DrawInfGame();

    char moving; // сторона в яку рухається змія

    while (!gameOver)
    {
        DrawMap();
        Input();
        Logic();
        Sleep(40);
        
        if (dir == LEFT || dir == RIGHT)
            Sleep(5);

        Sleep(50);

        if (dir == UP || dir == DOWN)
            Sleep(40);
    }
    cout << endl;

    system("pause");
}
