#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

char board[100][100];
int xKing1, yKing1, xKing2, yKing2, xRook1, yRook1, xRook2, yRook2;
int boardSize = 8, newSize;
int turn = 1; //cpu playes first
bool isRunning = 1, draw, mate;

void changeBoardSize();
void displayStartingScreen();
void exitGame();
void printEmptyBoard();
void printBoard();
void genKing2();
void genKing1();
void genRook1();
void genRook2();
void generateFigures();
void playerMove();

int main()
{
    int option;
    do
    {
        displayStartingScreen();
        cin >> option;
        if (option == 1)
        {
            generateFigures();
            printBoard();
            while (draw != 1 || mate != 1)
            {
                if (turn % 2 == 0)
                {
                    playerMove();
                    turn++;
                    printBoard();
                }
                else
                {
                    //cpuMove();
                    turn++;
                }
            }
            //count turns
        }
        else if (option == 2)
        {
            changeBoardSize();
        }
        else if (option == 3)
        {
            exitGame();
        }
        else
        {
            cout << "Invalid menu selection" << endl;
        }

    } while (isRunning);

    return 0;
}
void displayStartingScreen()
{
    cout << "--------------------" << endl;
    cout << "1. Start new game" << endl;
    cout << "2. Change board size" << endl;
    cout << "3. Exit" << endl;
    cout << "--------------------" << endl;
    cout << "Select a number: " << endl;
}
void changeBoardSize()
{
    cout << "Enter the new board size" << endl;
    cin >> newSize;
    while (newSize == boardSize)
    {
        cout << "! Enter different board size !" << endl;
        cin >> newSize;
    }
    boardSize = newSize;
    cout << "Board size changed to: " << newSize << "x" << newSize << endl;
}
void exitGame()
{
    cout << "...exiting" << endl;
    isRunning = 0;
}
void printEmptyBoard()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            cout << "-";
        }
        cout << endl;
    }
    cout << endl;
}
void genKing2()
{
    srand(time(0));
    xKing2 = (rand() % boardSize) + 0;
    yKing2 = (rand() % boardSize) + 0;
    //cout<<"King2 spawned at "<<xKing2<<", "<<yKing2<<endl;
}
void genKing1()
{
    srand(time(0));
    do
    {
        xKing1 = (rand() % boardSize) + 0;
        yKing1 = (rand() % boardSize) + 0;
    } while ((xKing1 >= xKing2 - 1 && xKing1 <= xKing2 + 1) && (yKing1 >= yKing2 - 1 && yKing1 <= yKing2 + 1));
    //cout<<"King1 spawned at "<<xKing1<<", "<<yKing1<<endl;
}
void genRook1()
{
    srand(time(0));
    do
    {
        xRook1 = (rand() % boardSize) + 0;
        yRook1 = (rand() % boardSize) + 0;
    } while ((xRook1 == xKing2 && yRook1 == yKing2) || (xRook1 == xKing1 && yRook1 == yKing1));
    //cout<<"Rook1 spawned at "<<xRook1<<", "<<yRook1<<endl;
}
void genRook2()
{
    srand(time(0));
    do
    {
        xRook2 = (rand() % boardSize) + 0;
        yRook2 = (rand() % boardSize) + 0;
    } while ((xRook2 == xKing2 && yRook2 == yKing2) || (xRook2 == xKing1 && yRook2 == yKing1) || (xRook2 == xRook1 && yRook2 == yRook1));
    //cout<<"Rook2 spawned at "<<xRook2<<", "<<yRook2<<endl;
}
void generateFigures()
{
    genKing2();
    genKing1();
    genRook1();
    genRook2();
}
void printBoard()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (xKing2 == i && yKing2 == j)
            {
                cout << "V";
            }
            else if (xKing1 == i && yKing1 == j)
            {
                cout << "K";
            }
            else if (xRook1 == i && yRook1 == j)
            {
                cout << "1";
            }
            else if (xRook2 == i && yRook2 == j)
            {
                cout << "2";
            }
            else
            {
                cout << "-";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void playerMove()
{
    char figure;
    int x, y;
    do
    {
        cout<<"Current king position "<<xKing1<<", "<<yKing1<<endl;
        cout<<"Your turn, enter coordinates in format P X Y"<<endl;
        cin>>figure>>x>>y;
        if (x < 0 || y < 0 || x > boardSize || y > boardSize)
        {
            cout << "Invalid coordinates" << endl;
        }
        else if (figure == 'K')
        {
            if (x < xKing1 - 1 || y < yKing1 - 1 || x > xKing1 + 1 || y > yKing2 + 1)
            {
                cout << "Invalid coordinates, king can only move 1 tile" << endl;
            }
            else if ((x >= xKing2 - 1 && x <= xKing2 + 1) && (y >= yKing2 - 1 && y <= yKing2 + 1) || x == xRook1 || y == yRook1 || x == xRook2 || y == yRook2)
            {
                cout << "Illegal move" << endl;
            }
            else
            {
                xKing1 = x;
                yKing1 = y;
                break;
            }    
        }
        else if (figure == '1')
        {
            //to do
            xRook1 = x;
            yRook1 = y;
        }
        else if (figure == '2')
        {
            //to copy
            xRook2 = x;
            yRook2 = y;
        }
        else
        {
            cout << "Invalid figure" << endl;
        }

    } while (true);
}