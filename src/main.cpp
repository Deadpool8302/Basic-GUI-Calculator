#include <iostream>
#include "consoleHandle.h"
#include <math.h>
#include <string>

/**
*   Helping Functions :
    -> _getch() :
            Takes a character as an input as soon as user presses a keyboard key.
            Can also take input of various keys like 'Enter', 'Arrow Keys' and return thier ascii value based on the operating system.

    -> cin.ignore() :
            _getch() when used after cin behaves wierdly. cin.ignore() counters it. It ignores certain inputs from keyboard.
            By Default ignores 1 character;

    -> gotoxy(int x, int y) :
            moves the cursor to position (x, y) on the console. For more Info read consoleHandle.hpp
    -> clrscr() :
            clears the console window. For more Info read consoleHandle.hpp
*/

using namespace std;

void clearLine(int x1, int x2, int y); // display ' ' from (x1, y) to (x2, y)

void putLine(int x, int y, string str); // display a string at (x, y)

int main()
{
    int input;
    int x = 0, y = 0, max_col = 3, max_row = 4;
    double a = 0, b = 0;
    char operand;

    while (true)
    {
        clrscr(); // clear the screen

        putLine(20, 1, "Basic GUI Calculator\n");
        putLine(20, 2, "Made by :- Bhavye Goel");
        putLine(20, 4, "Use W,A,S,D to move the cursor");
        putLine(20, 5, "Press Enter to give the input and press a button");

        if (y == 0)putLine(0, 0, "> ");     // cursor for first row
        else putLine((5 * x), y, "[   ]"); // normal cursor

        gotoxy(2, 0); cout << a;

        putLine(2, 1, "+");   putLine(7, 1, "-");   putLine(12, 1, "C");
        putLine(2, 2, "*");   putLine(7, 2, "/");   putLine(12, 2, "=");
        putLine(1, 3, "rtX"); putLine(6, 3, "x^2"); putLine(11, 3, "END");

        // cursor movements based on input
        input = _getch();
        if (input == 'w') y--;
        if (input == 'a') x--;
        if (input == 's') y++;
        if (input == 'd') x++;

        if (x == max_col || x == -1) x = 0;
        if (y == max_row || y == -1) y = 0;

        // button actions based on input
        if (y == 0 && input == 13) { // input line (first row)
            clearLine(2, 15, 0);
            cin >> a;
        }

        else if (x == 2 && y == 1 && input == 13) a = 0; // Clear button (C)
        else if (x == 2 && y == 2 && input == 13) {     //  Equal button (=)
            if (operand == '+') a += b;
            if (operand == '-') a -= b;
            if (operand == '*') a *= b;
            if (operand == '/') a /= b;
            if (operand == 's') a *= a;
            if (operand == 'r') a = sqrt(a);
        }

        else if (x == 0 && y == 3 && input == 13) { a = sqrt(a); operand = 'r'; }
        else if (x == 1 && y == 3 && input == 13) { a *= a; operand = 's'; }
        else if (x == 2 && y == 3 && input == 13) break;

        else if (input == 13) {
            clearLine(2, 15, 0);    // to clear previous input (a)
            putLine(0, 0, "> ");
            cin >> b;
            cin.ignore();
            if (x == 0 && y == 1) { a = a + b; operand = '+'; }
            else if (x == 1 && y == 1) { a = a - b; operand = '-'; }
            else if (x == 0 && y == 2) { a = a * b; operand = '*'; }
            else if (x == 1 && y == 2) { a = a / b; operand = '/'; }

        }
    }
}

void clearLine(int x1, int x2, int y)
{
    gotoxy(x1, y);
    for (int i = 0; i < (x2 - x1 + 1); i++) cout << " ";
    gotoxy(x1, y);
}

void putLine(int x, int y, string str)
{
    gotoxy(x, y);
    cout << str;
}



