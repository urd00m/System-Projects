#include <stdio.h>

// predeclaration
int get_y2(void); //returns -5 with the statically linked library
extern int y2; //use ld_preload global variable

// main function
int main(){
    printf("Press Enter to repeat\n\n");
    do{
	// Do division by zero
	int y = 5;
	int x = 5;
	printf("%d\n", y2);
	y2 = -5;
	x = 5/(y+y2);
	printf("Divided by zero finished %d\n", x);
    } while (getchar() == '\n');

    return 0;
}
