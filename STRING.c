#ifndef __MYFUNCS
#define __MYFUNCS
#include"MyFuncs.h"
#endif


void insert(string str, int show, int i, int j);

//         STRING-RELATED FUNCTION IMPLEMENTATIONS

string getstr(char *msg, int show){
    printf("%s", msg);
    string str = initstr();
    node *current = str.start, *mediator = NULL;
    int i=0, j = 0;
    while(1){
        int temp = getch();

        // Processing the read character
        if (temp == '\n') {printf("\n"); str.start->value = 'N'; break;}
        else if (temp == 127){
            if (current == str.start) continue;
            printf("\b \b");
            current->next->prev = current->prev;
            current->prev->next = current->next;
            mediator = current; current = current->prev; 
            free(mediator);
            i--;j--;
            insert(str, show, i, j);
            continue;
        }   
        else if (temp == 27){                                                   // 27 is ascii of Esc key
            temp = getch();
            if (temp == 91){                                                    // 91 is the ascii of open square bracket [
                temp = getch();
                if (temp == 67){                                                // In terminal when you press arrow key the input signal is actually 27 91 (65/66/67/68)
                    if (current->next == str.end) continue;
                    else current = current->next;
                    printf("\033[C"); // '\033' means print the character with ascii value 33 in octal notation (27 in decimal)
                    j++;
                    continue;
                }
                if (temp == 68){
                    if (current == str.start) continue;
                    else current = current->prev;
                    printf("\033[D");
                    j--;
                    continue;
                }
                if (temp == 65 || temp == 66){
                    str.start->value = (temp == 65)?'U':'D';
                    break;
                }
            }
            if (temp == 27){
                str.start->value = 'L';
                break;
            }
        }

        // Adding and printing the processed character
        mediator = (node*) malloc(sizeof(node));
        mediator->next = current->next; mediator->prev = current;
        current = current->next = (current->next)->prev = mediator;
        current->value = temp;
        insert(str, show, i, j);
        i++;j++;
    }
    str.length = i; str.cursor = j;
    return str;
}

//     -----------------------------insert()-----------------------------

void insert(string str, int show, int i, int j){
    if (show == 1){
        for (int k = 0; k <i-j; k++) printf("\033[C");
        str.end->value = '\0';
        printf("\r"); // \r deletes the output of the line behind the cursor
        strprint(str);
        str.end->value = '\n';
        for (int k = 0; k < (i-j); k++) printf("\b"); // \b char moves the cursor back one space
    }
    else {
        for (int k = 0; k < (i-j); k++) printf("\033[C");
        printf("*");
        for (int k = 0; k < (i-j); k++) printf("\b");
    }
}

//        ----------------------------freestr()-----------------------------

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

//           --------------------------strprint()-----------------------

void strprint(string str){
    node *current = str.start->next;  
    while(1){
        printf("%c", current->value);
        if (current->next != NULL) current = current->next;
        else break;
    }
}

//           --------------------------editstr()-----------------------

void editstr(string str, int j){
    str.start->value = '\0';
    int i = str.length;
    if (j > i) j = i;
    int del = i-j;
    node *mediator = NULL, *current;
    if (j < del){
        current = str.start; 
        for (int k = 0; k < j && current->next != str.end; k++){current = current->next;}
    }
    else{
        current = str.end->prev;
        for (int k = 0; k < del && current != str.start; k++){current = current->prev;}
    }
    insert(str, 1, i, j);

/*-----------------------------SAME CODE AS THE CORE OF getstr() BUT WITH PRESET VALUE OF current AND j---------------------------------------------*/ 

    while(1){
        int temp = getch();

        // Processing the read character
        if (temp == '\n') {printf("\n"); str.start->value = 'N'; break;}
        else if (temp == 127){
            if (current == str.start) continue;
            printf("\b \b");
            current->next->prev = current->prev;
            current->prev->next = current->next;
            mediator = current; current = current->prev; 
            free(mediator);
            i--;j--;
            insert(str, 1, i, j);
            continue;
        }   
        else if (temp == 27){
            temp = getch();
            if (temp == 91){
                temp = getch();
                if (temp == 67){
                    if (current->next == str.end) continue;
                    else current = current->next;
                    printf("\033[C");
                    j++;
                    continue;
                }
                if (temp == 68){
                    if (current == str.start) continue;
                    else current = current->prev;
                    printf("\033[D");
                    j--;
                    continue;
                }
                if (temp == 65 || temp == 66){
                    str.start->value = (temp == 65)?'U':'D';
                    break;
                }
            }
            if (temp == 27){
                str.start->value = 'L';
                break;
            }
        }

        // Adding and printing the processed character
        mediator = (node*) malloc(sizeof(node));
        mediator->next = current->next; mediator->prev = current;
        current = current->next = (current->next)->prev = mediator;
        current->value = temp;
        insert(str, 1, i, j);
        i++;j++;
    }
    str.length = i; str.cursor = j;    
}

//      ------------------------------------------initstr()--------------------------------------

string initstr(){
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
    return str;
}