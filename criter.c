#include "__text.h"
#include <unistd.h>
#include <stdio.h>

void save(FILE* fd, text txt);

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Syntax: criter [filename]\n");
        return 1;
    }
    printf("\033[D\033[J");
    if (argc > 2) printf("Only the the first argument will be considered.\n\n");
    printf("Opening %s ...\n", argv[1]);
    FILE *fd = fopen(argv[1], "r"), *temp;
    text txt = initxt();
    if (fd != NULL){
        temp = stdin;
        stdin = fd;
        txt = editxt(txt, txt.lines, 2);
        stdin = temp;
        printf("The Buffer has been loaded(Press Esc twice to save and leave):\n\n");
        printf("=======================================================================\n\n");
        printxt(txt);
        fclose(fd);
    }
    else {
        printf("No file of such name exists.\nCreating new file.\n");
        printf("The Buffer has been loaded(Press Esc twice to save and leave):\n\n");
        printf("=======================================================================\n\n");
    }
    txt = editxt(txt, txt.lines, 1);
    fd = fopen(argv[1], "w");
    save(fd, txt);
    printf("=======================================================================\n");
    printf("Your buffer was sucessfully saved.\n");
    freetxt(txt);
    fclose(fd);
}

void save(FILE* fd, text txt){
    FILE* temp = stdout; stdout = fd;
    (txt.end->prev->value).end->value = '\0';
    printxt(txt);
    (txt.end->prev->value).end->value = '\n';
    stdout = temp;
}