#ifndef __MYFUNCS
#define __MYFUNCS
#include"MyFuncs.h"
#endif


//         STRING-RELATED FUNCTION IMPLEMENTATIONS

string getstring(char *msg, int show, char EOS){
    printf("%s", msg);
    node *current = NULL, *mediator = NULL;
    string str;
    int i=0,lines = 0, flag = 0;
    while(1){
        int temp = getch();
        if (temp == EOS) break;
        else if (temp == 10) {lines++; i=0;}
        else if (temp == 127){
            if (current->prev == NULL) continue;
            printf("\b \b");
            current = current->prev;
            str.end = current;
            free(current->next);
            current->next = NULL;
            continue;
        }
        if (show == 1) printf("%c", temp);
        else printf("*");
        mediator = (node*) malloc(sizeof(node));
        if (i != 0) current->next = mediator;
        else str.start = mediator;
        mediator->prev = current;
        current = mediator;
        current->value = temp;
        current->next = NULL;
        str.end = current;
        i++;
    }
    printf("\n"); return str;
}

void freestring(string str){
    node *current = str.end;
    node *prev = current->prev;
    while (prev != NULL){
        free(current);
        current = prev;
        prev = current->prev;
    }
    free(current);
}

void strprint(string str){
    node *current = str.start;
    while(current->next != NULL){
        printf("%c", current->value);
        current = current->next;
    }
    printf("%c\n", current->value);
}
