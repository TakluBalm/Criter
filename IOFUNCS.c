#ifndef __MYFUNCS
#include "MyFuncs.h"
#endif


int getch(){
    struct termios updated, old;
    tcgetattr(STDIN_FILENO, &old);
    updated=old;
    updated.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &updated);
    int c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return c;
}
