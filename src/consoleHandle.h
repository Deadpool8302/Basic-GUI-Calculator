#pragma once
#include <conio.h>
#include <windows.h>

/*
    gotoxy(short, short) and clrscr() were predefined functions in conio.h header file in older versions of c++.
    Since they are no longer available in modern versions of c++.
    I have used raw code of those functions (not coded by me)

    conio.h is included for _getch() function.
    _getch() takes a character as an input as soon as user presses a keyboard key.
    Depending on the OS and the version of C++ name of this function may vary like getch(), _getch()
*/

void gotoxy(short x, short y)
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);  // get console handle
    COORD cursor = { x+35, y+5 };
    SetConsoleCursorPosition(hc, cursor);  // set new cursor position
}

void clrscr()
{
    DWORD n;                         /* Number of characters written */
    DWORD size;                      /* number of visible characters */
    COORD coord = { 0 };               /* Top left screen position */
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    /* Get a handle to the console */
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(h, &csbi);

    /* Find the number of characters to overwrite */
    size = csbi.dwSize.X * csbi.dwSize.Y;

    /* Overwrite the screen buffer with whitespace */
    FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n); // diaplays ' ' through the whole console.
    GetConsoleScreenBufferInfo(h, &csbi);
    FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

    /* Reset the cursor to the top left position */
    SetConsoleCursorPosition(h, coord);
}
