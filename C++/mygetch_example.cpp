/*H**********************************************************************
* FILENAME :    mygetch_example.cpp
*
* DESCRIPTION :
*       Allows continual keyboard input, 1 key at a time.
*       This was designed for text based games.
*
* NOTES :
*       !!!!! This will not work naturally on windows!
*             termios.h is on Linux and MacOS !!!!!
*       Compiled using: g++ mygetch_example.cpp -o mygetch_example
* 
* AUTHOR :    Brandon Pirtle        START DATE :     4 Jul 15
*                                   EDIT  DATE :     9 Mar 16
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include <iostream>
    using std::cout;
    using std::endl;
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

enum Keys {
    RETURN      = 10,       // <Return> is really a '\n' (on Mac/Linux)
    ENTER       = 13,       // Windows style <Enter> is '\r'
    ESCAPE      = 27,       // Escape key character
    SPACE_BAR   = 32,       // Space  key character
    GET_READY   = 91,       // After an ESC, this preceeds a named key
    UP_ARROW    = 9999965,  // to get out of the way of ASCII and UNICODE
    DOWN_ARROW  = 9999966,  // (highest unicode is 1114111)
    RIGHT_ARROW = 9999967,  // (which is 10ffff in hex)
    LEFT_ARROW  = 9999968
};

int mygetch();
int mygetch_helper();

int main(int argc, char *argv[]) {
    cout << "Press <CTRL> + C to exit...\n\n";
    while(1) {
        int c = mygetch();
        if (c == UP_ARROW) {
            cout << "UP";
        }
        else if (c == DOWN_ARROW) {
            cout << "DOWN";
        }
        else if (c == LEFT_ARROW) {
            cout << "LEFT";
        }
        else if (c == RIGHT_ARROW) {
            cout << "RIGHT";
        }
        else if (c == ESCAPE) {
            cout << "ESCAPE";
        }
        else if (c == SPACE_BAR) {
            cout << "SPACE BAR";
        }
        else {
            cout << static_cast<char>(c);
        }
        cout << endl;
    }
    return 0;
}

/* If you see ESCAPE, there might be a named key coming.
   Second code should be GET_READY, followed by a key code.
   Add 9999900 to move out of the way of printable characters. */
int mygetch () {
    int ch = mygetch_helper();
    if (ch == ESCAPE)
        if (mygetch_helper() == GET_READY)
            ch = 9999900 + mygetch_helper();
    return ch;
}

int mygetch_helper () {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
