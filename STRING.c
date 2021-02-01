#ifndef __MYFUNCS
#define __MYFUNCS
#include"MyFuncs.h"
#endif


//         STRING-RELATED FUNCTION IMPLEMENTATIONS

string getstr(char *msg, int show){
    printf("%s", msg);
    string str;
    do
    str.start = (node*) malloc(sizeof(node));
    while (str.start == NULL);
    do 
    str.end = (node*) malloc(sizeof(node));
    while (str.end == NULL);   
    str.start->next = str.end; str.end->prev = str.start;
    str.start->prev = str.end->next = NULL; 
    str.start->value = '\0'; str.end->value = '\n';
    node *current = str.start, *mediator = NULL;
    int i=0, j = 0;
    while(1){
        int temp = getch();

        // Processing the read character
        if (temp == '\n') {printf("\n"); break;}
        else if (temp == 127){
            if (current == str.start) continue;
            printf("\b \b");
            current = current->prev;
            current->next = (current->next)->next; 
            free((current->next)->prev);
            (current->next)->prev = current;
            i--;j--;
            continue;
        }
        else if (temp == 27){
            temp = getch();
            if (temp == 91)
            {
                temp = getch();
                if (temp == 67){
                    if (current->next == str.end) continue;
                    else current = current->next;
                    printf("\033[C");
                    j--;
                    continue;
                }
                if (temp == 68){
                    if (current->prev == str.start || current->prev == NULL) continue;
                    else current = current->prev;
                    printf("\033[D");
                    j--;
                    continue;
                }
            }
        }

        // Adding and printing the processed character
        mediator = (node*) malloc(sizeof(node));
        mediator->next = current->next; mediator->prev = current;
        current = current->next = (current->next)->prev = mediator;
        current->value = temp;
        if (show == 1){
            for (int k = 0; k < j; k++) printf("\b");
            str.end->value = '\0';
            strprint(str);
            str.end->value = '\n';
            for (int k = 0; k < (i-j); k++) printf("\b");
        }
        else printf("*");
        i++;j++;
    }
    str.length = i; return str;
}

void freestr(string str){
    node *current = str.start, *next = str.start->next;
    while(1){
        free(current);
        if (next->next == NULL){
            free(next);
            break;
        }
        current = next;
        next = next->next;
    }
}

void strprint(string str){
    node *current = str.start->next;  
    while(1){
        printf("%c", current->value);
        if (current->next != NULL) current = current->next;
        else break;
    }
}
