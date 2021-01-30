#include <stdio.h>
#include <termios.h>
#include<unistd.h>

int getch();
int customread(FILE *fd);

int main(int argc, char *argv[]){
    char s[100000];
    FILE *fd = fopen(argv[1],"r");
    int i = 0, temp;
    if (fd != NULL){
        for (temp = customread(fd); temp != EOF; temp = customread(fd)){
            s[i]=temp;
            i++;
        }
        fclose(fd);
    }
    printf("%s", s);
    fd = fopen(argv[1], "w");
    while(1){
        int temp;
        temp = getch();
        // input character is not a special character
        //                              |
        //  ------------------------------------------------------
        if (temp != 19 && temp != '`' && temp != 127 && temp != 10){
            printf("%c", temp);
            s[i] = temp;
            i++;
            continue;
        }
        // ` is our exit key

        else if (temp == '`'){
            FILE *tempout = stdout;
            stdout = fd;
            s[i]='\0';
            printf("%s",s);
            stdout = tempout;
            fclose(fd);
            printf("\nBuffer Successfully Saved\n");
            break;
        }

        // 19 is the ascii for cntrl+S

        // else if (temp == 19){                       
        //     FILE *tempout = stdout;
        //     stdout = fd;
        //     s[i]='\0';
        //     printf("%s",s);
        //     stdout = tempout;
        //     continue;
        // }

        // 127 is the ascii for backspace

        else if (temp == 127){
            printf("\b \b");
            i--;
            continue;
        }
        // 10 is the ascii of enter key
        else{
            printf("\n");
            s[i] = '\n';
            i++;
            continue;
        }
    }
}

int getch(){
    struct termios new, old;
    tcgetattr(STDIN_FILENO, &old);
    new=old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    int c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return c;
}

int customread(FILE* fd){
    FILE* tempin = stdin;
    stdin = fd;
    int temp = getch();
    stdin = tempin;
    return temp;
}