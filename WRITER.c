#ifndef __MYFUNCS
#define __MYFUNCS
#include"MyFuncs.h"
#endif

//      Writer-Specific Functions are Implemented here

text getxt(){
    text txt;
    txt.start = (line*) malloc(sizeof(line)), txt.end = (line*) malloc(sizeof(line));
    txt.start->next = txt.end; txt.end->prev = txt.start;
    txt.start->prev = txt.end->next = NULL;
    string str = initstr();
    txt.start->value = txt.end->value = str;
    line *current = txt.start, *mediator = NULL;
    int i=0, j=0;
    while(1){
        if ((current->value).start->value == 'U'){
            if (current->prev == txt.start) continue;
            printf("\033[A");
            current = current->prev; j--;
            for (int k = 0; k < (current->value).cursor; k++) printf("\b");
            editstr(current->value, (current->next->value).cursor);
            continue;
        }
        if ((current->value).start->value == 'D'){
            if (current->next == txt.end) continue;
            printf("\033[B");
            current = current->next; j++;
            for (int k = 0; k < (current->value).cursor; k++) printf("\b");
            editstr(current->value, (current->value).cursor);
            continue;
        }
        if ((current->value).start->value == 'L') break;
        mediator = (line*) malloc(sizeof(line));
        mediator->next = current->next; mediator->prev = current;
        current = current->next = current->next->prev = mediator;
        current->value = getstr("", 1);
        i++;j++;
    }
    txt.lines = i; return txt;
}

void printxt(text txt){
    line* current = txt.start->next;
    while (current != txt.end){
        strprint(current->value);
        current = current->next;
    }
}

void freetxt(text txt){
    line* current = txt.end->prev;
    while(current != txt.start){
        freestr(current->value);
        current = current->prev;
        free(current->next);
    }
    freestr(txt.start->value);free(txt.end); free(txt.start);
}