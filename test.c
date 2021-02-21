#include "__io.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	printf("Hello\033[4D\t");
	getch();
}
