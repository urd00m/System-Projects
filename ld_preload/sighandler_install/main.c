#include <stdio.h>

// predeclaration
int get_y2(void); //returns -5 with the statically linked library

// main function
int main(){
    printf("Press Enter to repeat\n\n");
    do{
	// Do division by zero
	int y = 5;
	int x = 5;
	x = 5/(y+get_y2());
	printf("Divided by zero finished %d\n", x);
    } while (getchar() == '\n');

    return 0;
}
