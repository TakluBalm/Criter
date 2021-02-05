#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>


//      Custom structs

typedef struct node{
    int value;
    struct node *next;
    struct node *prev;
}node;
typedef struct string{
    int length, cursor;
    node *start;
    node *end;
}string;

// A line is like a node but instead of charcter it contains a whole string
typedef struct line{        
    string value;
    struct line* next;
    struct line* prev;
}line;
typedef struct text{
    int lines;
    line* start;
    line* end;
}text;

//          FUNCTIONS IN THIS HEADER

int getch();
string initstr();
string getstr(char *msg, int show);
void editstr(string str, int j);
void freestr(string str);
void strprint(string str);
text getxt();
void freetxt(text txt);
void printxt(text txt);

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
#include "WRITER.c"