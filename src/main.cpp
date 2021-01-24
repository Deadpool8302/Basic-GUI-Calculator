#include <iostream>
#include "consoleHandle.h"
#include <math.h>
#include <cmath>
#include <string>
#include <vector>

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

#define PI 3.14159265      // value of pi

void clearLine(int x1, int x2, int y); // displayFormat ' ' from (x1, y) to (x2, y)

void putLine(int x, int y, string str); // displayFormat a string at (x, y)

double factorial(double x);  // Creating a factorial function 

void displayHelp();   // Function to display various instructions 


// Creating a Button class to store all the buttons.
class Button {
public:
    string symbol;
    int x, y;

    Button(int a, int b, string str, vector<Button>& allButtons) {         // Constructor to store symbol and position of the buttons
        symbol = str;
        x = a;
        y = b;
        allButtons.push_back(*this);
    }

    void draw() {                                     // Method function to display the buttons on screen 
        putLine(x, y, symbol);
    }

    bool hit(int a, int b) {
        if (((2+(5*a) == x) || (1+(5*a) == x)) && (b == y)) return true;          // Checking if the button is pressed or not.
        
        return false;
    }

};

int main()
{
    int input;
    int x = 0, y = 0, max_col = 4, max_row = 7;
    double a = 0, b = 0;
    string operand; 
    vector<double> memory;
  
    vector<Button> allButtons;      // Creating a vector of Button class, containing all the buttons.
     

    // Creating Buttons.....

    Button c(2, 1, "C", allButtons);         Button fac(7, 1, "X!", allButtons);      Button per(12, 1, "%", allButtons);         Button div(17, 1, "/", allButtons);
    Button sine(1, 2, "sin", allButtons);    Button cosine(6, 2, "cos", allButtons);  Button tangent(11, 2, "tan", allButtons);   Button mul(17, 2, "*", allButtons);
    Button power10(1, 3, "10^", allButtons); Button powerE(6, 3, "e^x", allButtons);  Button mod(11, 3, "MOD", allButtons);       Button sub(17, 3, "-", allButtons);
    Button logB10(1, 4, "log", allButtons);  Button logBe(6, 4, "lnX", allButtons);   Button rnd(11, 4, "rnd", allButtons);       Button add(17, 4, "+", allButtons);
    Button root(1, 5, "rtX", allButtons);    Button power(6, 5, "x^y", allButtons);   Button sq(11, 5, "x^2", allButtons);        Button eq(17, 5, "=", allButtons);
    Button mAdd(1, 6, "ME+", allButtons);    Button mSub(6, 6, "ME-", allButtons);    Button mSave(11, 6, "MeS", allButtons);     Button end(16, 6, "END", allButtons);

    

    while (true)
    {
        
        clrscr(); // clear the screen

        putLine(26, 1, "Basic GUI Calculator");
        putLine(26, 2, "Made by :- Bhavye Goel");
        putLine(26, 4, "Press 'H' for help");
        putLine(26, 5, "Press 'E' to clear the memory");

        putLine(1, 10, "Memory");              // Creating a memory space
        
        for (int i = 0; i < memory.size(); i++) {         // To display stored inputs in Memory
            gotoxy(1, (11 + i)); cout << memory[i];
        }

        if (y == 0)putLine(0, 0, "> ");            // cursor for first row
        else putLine((5 * x), y, "[   ]");       // normal cursor

        for (int i = 0; i < allButtons.size(); i++) {    // To display all the Buttons 
            allButtons[i].draw();
        }
      
        gotoxy(2, 0); cout << a;

        gotoxy(84, 0);

        input = _getch();

        // Creating a HELP screen with various instructions
        if (input == 'h') {
            displayHelp();
            continue; 
        }

        // cursor movements based on input
        if (input == 'w' ) y--;
        if (input == 'a' ) x--;
        if (input == 's' ) y++;
        if (input == 'd' ) x++;

        if (x == max_col) x = 0;
        if (y == max_row) y = 0;
        if (x == -1) x = (max_col - 1);
        if (y == -1) y = (max_row - 1);

        if (input == 'e') memory.clear();

        // button actions based on input
        if (input == 13) {
            if (y == 0) {                   // input line (first row)
                clearLine(2, 15, 0);
                cin >> a;
            }

            else if (mSave.hit(x, y)) { memory.push_back(a); }      // Storing input in memory 
            else if (mAdd.hit(x, y)) {                              // To add the input in the last stored memory 
                if (memory.size() == 0) memory.push_back(a);
                else memory[memory.size() - 1] += a;
            }
            else if (mSub.hit(x, y)) {                                // To subract the input from the last stored memory 
                if (memory.size() == 0) memory.push_back(0 - a);
                else memory[memory.size() - 1] -= a;

            }
            else if (per.hit(x, y)) { a /= 100; operand = 'p'; }  //Percentage button (%) 
            else if (fac.hit(x, y)) { a = factorial(a); operand = 'f'; }   // Factorial button (X!)

            else if (sine.hit(x, y))     a = sin(a * PI / 180);    // Button to calculate sine (sin)
            else if (cosine.hit(x, y))   a = cos(a * PI / 180);    // Button to calculate cosine (cos)
            else if (tangent.hit(x, y))  a = tan(a * PI / 180);    // Button to calculate tangent (tan)

            else if (logB10.hit(x, y)) a = log10(a);   // Log to the base 10 button (log)
            else if (logBe.hit(x, y)) a = log(a);   // Natural Log button (lnX)

            else if (power10.hit(x, y)) a = pow(10, a);  // 10 Raise to the power input button (10^)
            else if (powerE.hit(x, y)) a = exp(a);  // Exponential function button (e^x)

            else if (rnd.hit(x, y)) a = round(a);   // Rounding off to nearest value (rnd)

            else if (c.hit(x, y)) a = 0;           // Clear button (C)
            else if (eq.hit(x, y)) {               //  Equal button (=)
                if (operand == "+") a += b;
                if (operand == "-") a -= b;
                if (operand == "*") a *= b;
                if (operand == "/") a /= b;
                if (operand == "s") a *= a;
                if (operand == "r") a = sqrt(a);
                if (operand == "p") a /= 100;
                if (operand == "^") a = pow(a, b);
                if (operand == "f") a = factorial(a);
            }


            else if (root.hit(x, y)) { a = sqrt(a); operand = 'r'; }    // Square root button (rtx)
            else if (sq.hit(x, y)) { a *= a; operand = 's'; }       // Square button (x^2)
            else if (end.hit(x, y)) break;   // END button (END)

            else {
                clearLine(2, 15, 0);    // to clear previous input (a)
                putLine(0, 0, "> ");
                cin >> b;
                cin.ignore();
                if (add.hit(x, y)) { a = a + b; operand = '+'; }
                else if (sub.hit(x, y)) { a = a - b; operand = '-'; }
                else if (mul.hit(x, y)) { a = a * b; operand = '*'; }
                else if (div.hit(x, y)) { a = a / b; operand = '/'; }
                else if (power.hit(x, y)) { a = pow(a, b); operand = '^'; }     // Raise to power button (x^y)
                else if (mod.hit(x, y)) { a = fmod(a, b); operand = "mod"; }     // Modulus button (MOD)

            }
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

double factorial(double x) {
    for (int i = (x-1); i >= 1; i--) {
        x *= i;
    }
    return x;
}

void displayHelp() {

    int input; 

    while (true) {

        clrscr();
        putLine(-20, 0, "-> Use W,A,S,D to move the cursor");
        putLine(-20, 1, "-> Press Enter to give the input and to press a button");
        putLine(-20, 2, "-> To toggle between your previously entered inputs use \"Up\" and \"Down\" arrow keys.");
        putLine(-20, 3, "-> To calculate Sine, Cosine and Tangent value, enter value in degrees");
        putLine(-20, 4, "-> Press (END) button to exit the calculator");
        putLine(-20, 5, "-> (10^) button calculates 10 raised to the power input give");
        putLine(-20, 6, "-> (MOD) button calculates the modulus of the given inputs.");
        putLine(-20, 7, "-> (log) button calculates log of the input to the base 10");
        putLine(-20, 8, "-> (lnX) button calculates log of the input to the base e");
        putLine(-20, 9, "-> (rnd) button rounds off the input to its nearest value");
        putLine(-20, 10, "-> (rtX) button rounds off the input to its nearest value");
        putLine(-20, 11, "-> (ME+) button adds the input to the last stored value in memory");
        putLine(-20, 12, "-> (ME-) button subracts the input from the last stored value in memory");
        putLine(-20, 13, "-> (Mes) button stores the input in the memory");

        putLine(10, 15, "Press ESC to return");

        input = _getch();
        if (input == 27) break;          // Exiting the help screen

    }
}
