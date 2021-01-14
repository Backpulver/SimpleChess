/**
*  
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Yoan Hristov
* @idnumber 62593
* @compiler GCC
*
* <file with helper functions>
*
*/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <string>
using std::cout; //cstdlib breaks the using namespace std;
using std::endl;

char board[100][100];
int xKing1, yKing1, xKing2, yKing2, xRook1, yRook1, xRook2, yRook2;
int boardSize = 8, newSize;
int turn = 1; //cpu playes first
bool isRunning = 1, draw, mate, capturedR1, capturedR2;

void changeBoardSize();
void displayStartingScreen();
void exitGame();
void printBoard();
void genKing2();
void genKing1();
void genRook1();
void genRook2();
void generateFigures();
void playerMove();
void cpuMove();
void cpuKingMove();

int main()
{
    int option;
    do
    {
        displayStartingScreen();
        std::cin >> option;
        if (option == 1)
        {
            draw = 0;
            mate = 0;
            capturedR1 = 0;
            capturedR2 = 0;
            generateFigures();
            while (draw != 1 && mate != 1)
            {
                if (turn % 2 == 0)
                {
                    printBoard();
                    cout << "King position " << xKing1 << ", " << yKing1 << endl; //just so we dont hurt our eyes counting rows and cols
                    cout << "Rook1 position " << xRook1 << ", " << yRook1 << endl;
                    cout << "Rook2 position " << xRook2 << ", " << yRook2 << endl;
                    cout << "Enemy King is at " << xKing2 << ", " << yKing2 << endl;
                    playerMove();
                    turn++;
                }
                else
                {
                    cpuMove();
                    turn++;
                }
            }
            if (mate)
            {
                cout << "MATE in " << turn / 2<< " moves" << endl; //logic about turns could be wrong
            }
            else if (draw)
            {
                cout << "STALEMATE in " << turn / 2<< " moves" << endl;
            }
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
    std::cin >> newSize;
    while (newSize == boardSize)
    {
        cout << "! Enter different board size !" << endl;
        std::cin >> newSize;
    }
    boardSize = newSize;
    cout << "Board size changed to: " << newSize << "x" << newSize << endl;
}
void exitGame()
{
    cout << "...exiting" << endl;
    isRunning = 0;
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
void generateFigures() //so we dont call 'em one by one in main
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
            if (xKing2 == j && yKing2 == i)
            {
                cout << "V";
            }
            else if (xKing1 == j && yKing1 == i)
            {
                cout << "K";
            }
            else if (xRook1 == j && yRook1 == i)
            {
                cout << "1";
            }
            else if (xRook2 == j && yRook2 == i)
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
        if (capturedR1 == 1 && capturedR2 == 1)
        {
            draw = 1;
            break;
        }

        cout << "Your turn, enter coordinates in format P X Y" << endl;
        std::cin >> figure >> x >> y;
        if (x < 0 || y < 0 || x >= boardSize || y >= boardSize)
        {
            cout << "Invalid coordinates" << endl;
        }
        else if (figure == 'K')
        {
            if (x < (xKing1 - 1) || y < (yKing1 - 1) || x > (xKing1 + 1) || y > (yKing1 + 1))
            {
                cout << "Invalid coordinates, the king can only move 1 tile" << endl;
            }
            else if (x == xKing1 && y == yKing1)
            {
                cout << "The king doesnt move" << endl;
            }
            else if ((x >= xKing2 - 1 && x <= xKing2 + 1) && (y >= yKing2 - 1 && y <= yKing2 + 1) || (x == xRook1 && y == yRook1) || (x == xRook2 && y == yRook2))
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
            if (capturedR1)
            {
                cout << "This piece is no loger in play" << endl;
            }
            else if ((x == xKing1 && y == yKing1) || (x == xRook2 && y == yRook2))
            {
                cout << "Illegal move, a piece has already occupied this square" << endl;
            }
            else if ((x == xRook1 && y != yRook1) || (x != xRook1 && y == yRook1))
            {
                xRook1 = x;
                yRook1 = y;
                break;
            }
            else
            {
                cout << "Illegal move" << endl;
            }
        }
        else if (figure == '2')
        {
            if (capturedR2)
            {
                cout << "This piece is no loger in play" << endl;
            }
            else if ((x == xKing1 && y == yKing1) || (x == xRook1 && y == yRook1))
            {
                cout << "Illegal move, a piece has already occupied this square" << endl;
            }
            else if ((x == xRook2 && y != yRook2) || (x != xRook2 && y == yRook2))
            {
                xRook2 = x;
                yRook2 = y;
                break;
            }
            else
            {
                cout << "Illegal move" << endl;
            }
        }
        else
        {
            cout << "Invalid figure" << endl;
        }

    } while (true);
}
void cpuMove()
{
    if (xKing2 == xRook1 || xKing2 == xRook2 || yKing2 == yRook1 || yKing2 == yRook2)
    {
        if ((xRook1 >= xKing2 - 1 && xRook1 <= xKing2 + 1) && (yRook1 >= yKing2 - 1 && yRook1 <= yKing2 + 1))
        {
            if (xRook1 != xRook2 && yRook1 != yRook2 && (xRook1 < xKing1 - 1 || xRook1 > xKing1 + 1 || xRook1 < yKing1 - 1 || xRook1 > yKing1 + 1)) //check if rook1 is defended
            {
                xKing2 = xRook1;
                yKing2 = yRook1;
                capturedR1 = 1;
                xRook1 = -1;
                yRook1 = -1;
            }
        }
        else if ((xRook2 >= xKing2 - 1 && xRook2 <= xKing2 + 1) && (yRook2 >= yKing2 - 1 && yRook2 <= yKing2 + 1))
        {
            if (xRook1 != xRook2 && yRook1 != yRook2 && (xRook2 < xKing1 - 1 || xRook2 > xKing1 + 1 || xRook2 < yKing1 - 1 || xRook2 > yKing1 + 1)) //check is rook2 is defended
            {
                xKing2 = xRook2;
                yKing2 = yRook2;
                capturedR2 = 1;
                xRook2 = -1;
                yRook2 = -1;
            }
        }
        else
        {
            //Cant capture, move
            cpuKingMove();
        }
    }
    else if ((xRook1 >= xKing2 - 1 && xRook1 <= xKing2 + 1) && (yRook1 >= yKing2 - 1 && yRook1 <= yKing2 + 1)) //check if king is next to rook1
    {
        if (xRook1 != xRook2 && yRook1 != yRook2 && (xRook1 < xKing1 - 1 || xRook1 > xKing1 + 1 || xRook1 < yKing1 - 1 || xRook1 > yKing1 + 1)) //check if rook1 is defended
        {
            xKing2 = xRook1;
            yKing2 = yRook1;
            capturedR1 = 1;
            xRook1 = -1;
            yRook1 = -1;
        }
        else
        {
            //Cant capture, move
            cpuKingMove();
        }
    }
    else if ((xRook2 >= xKing2 - 1 && xRook2 <= xKing2 + 1) && (yRook2 >= yKing2 - 1 && yRook2 <= yKing2 + 1)) //check if king is next to rook2
    {
        if (xRook1 != xRook2 && yRook1 != yRook2 && (xRook2 < xKing1 - 1 || xRook2 > xKing1 + 1 || xRook2 < yKing1 - 1 || xRook2 > yKing1 + 1)) //check is rook2 is defended
        {
            xKing2 = xRook2;
            yKing2 = yRook2;
            capturedR2 = 1;
            xRook2 = -1;
            yRook2 = -1;
        }
        else
        {
            //Cant capture, move
            cpuKingMove();
        }
    }
    else
    {
        //Nothing to do, move
        cpuKingMove();
    }
}
void cpuKingMove()
{
    if (xKing2 - 1 != xRook1 && xKing2 - 1 != xRook2 && xKing2 - 1 != xKing1 + 1 && xKing2 - 1 >= 0 && yKing2 != yRook1 && yKing2 != yRook2)
    {
        xKing2--;
    }
    else if (xKing2 + 1 != xRook1 && xKing2 + 1 != xRook2 && xKing2 + 1 != xKing1 - 1 && xKing2 + 1 < boardSize && yKing2 != yRook1 && yKing2 != yRook2)
    {
        xKing2++;
    }
    else if (yKing2 - 1 != yRook1 && yKing2 - 1 != yRook2 && yKing2 - 1 != yKing1 + 1 && yKing2 - 1 >= 0 && xKing2 != xRook1 && xKing2 != xRook2)
    {
        yKing2--;
    }
    else if (yKing2 + 1 != yRook1 && yKing2 + 1 != yRook2 && yKing2 + 1 != yKing1 - 1 && yKing2 + 1 < boardSize && xKing2 != xRook1 && xKing2 != xRook2)
    {
        yKing2++;
    }
    else if (xKing2 == xRook1 || xKing2 == xRook2 || yKing2 == yRook1 || yKing2 == yRook2)
    {
        //check and cant move 1 tile = mate
        if (xKing2 - 1 < 0 || yKing2 - 1 < 0 || xKing2 + 1 == boardSize || yKing2 + 1 == boardSize)
        {
            mate = 1;
        }
    }
    else if (xKing2 != xRook1 && xKing2 != xRook2 && yKing2 != yRook1 && yKing2 != yRook2)
    {
        //not in check and cant move 1 tile = stalemate
        if (xKing2 - 1 < 0 || yKing2 - 1 < 0 || xKing2 + 1 == boardSize || yKing2 + 1 == boardSize)
        {
            draw = 1;
        }
    }
    else
    {
        cout << "I died beep boop" << endl;
        mate = 1; //if we got this far, something is not right
    }

    /* initialize diagonal movement after fixing all other problems
    else if ((xKing2 - 1 != xRook1 && xKing2 - 1 != xRook2 && xKing2 - 1 != xKing1 + 1 && xKing2 - 1 >= 0) && (yKing2 - 1 != yRook1 && yKing2 - 1 != yRook2 && yKing2 - 1 != yKing1 + 1 && yKing2 - 1 >= 0))
    {
        xKing2--;
        yKing2--;
    }
    else if ((xKing2 - 1 != xRook1 && xKing2 - 1 != xRook2 && xKing2 - 1 != xKing1 + 1 && xKing2 - 1 >= 0) && (yKing2 + 1 != yRook1 && yKing2 + 1 != yRook2 && yKing2 + 1 != yKing1 - 1 && yKing2 + 1 < boardSize))
    {
        xKing2--;
        yKing2++;
    }
    else if ((xKing2 + 1 != xRook1 && xKing2 + 1 != xRook2 && xKing2 + 1 != xKing1 - 1 && xKing2 + 1 < boardSize) && (yKing2 - 1 != yRook1 && yKing2 - 1 != yRook2 && yKing2 - 1 != yKing1 + 1 && yKing2 - 1 >= 0))
    {
        xKing2++;
        yKing2--;
    }
    else if ((xKing2 + 1 != xRook1 && xKing2 + 1 != xRook2 && xKing2 + 1 != xKing1 - 1 && xKing2 + 1 < boardSize) && (yKing2 + 1 != yRook1 && yKing2 + 1 != yRook2 && yKing2 + 1 != yKing1 - 1 && yKing2 + 1 < boardSize))
    {
        xKing2++;
        yKing2++;
    }*/
}