#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

#define __MYFUNCS

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

int getch();                                // Reads the input data directly and returns the input signal as (int)


string initstr();                           // Initialises the start, end, length and cursor fields of string datatype and returns the initialised string
string getstr(char *msg, int show);         // Initialises the string and stores the input from the user
string concatnate(string str1, string str2);// Takes two strings and merges them to a single one. The initial two strings lose their meanings
string editstr(string str, int j, int show);// Edits the contents of an initialised string 
string breakstr(string* str, int j);        // Takes the string and breaks it into two. Returns the right broken string while the left one stays in the original 
void freestr(string str);                   // Frees all the heap memory allocated by the above functions 
void strprint(string str);                  // Prints the content of a string to the screen
int stringcmp(string s1, string s2);           // Checks the strings for equality
void insert(string str, int show, int i, int j);    // To support visual insertion of characters in the string


text initxt();                              // Initialises the start, end and lines fields in text datatype 
text getxt(int show);                       // Initialises and takes texxt input from the user  
text editxt(text txt, int j, int show);     // Edits the contents of an initialised text
void freetxt(text txt);                     // Frees all the allocated memory by the initxt(), getxt() and editxt() functions
void printxt(text txt);                     // Prints the contents of 'txt' on the screen
