//global constructor tests in c
#include <stdio.h>
__attribute__ ((constructor)) void food(void) {
	printf("foo is running and printf is available at this point\n");
}

int main(int argc, char* argv[]) {
	printf("main is running with\n");
}
