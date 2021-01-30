#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>


//      Custom structs

typedef struct node{
    char value;
    struct node *next;
    struct node *prev;
}node;
typedef struct string{
    node *start;
    node *end;
}string;


//          FUNCTIONS IN THIS HEADER

int getch();
string getstring(char *msg, int show, char EOS);
void freestring(string str);
void strprint(string str);
void mvcurrent(char dir, node* current, int current_line, int chars, string str);

//          I/O FUNCTIONS
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

#include "STRING.c"