#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/paging.h>

void kernel_main(void) {
	terminal_initialize();
        printf("Test Hello, kernel World!\n");
        printf("Test test test\n");
        printf("Test test test\n");
        printf("Test test test\n");
        printf("Test test test\n");
        printf("Test test test\n");
        printf("Test test test\n");
        for(long i = 0; i < 1000; i++) {
                printf("Line %c\n", i);
        }
        //column overflow test
        printf("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()askfhefhaldfalfleajkfj new line plese\n");
        printf("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()askfhefhaldfalfleajkfj new line plese\n");
        printf("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()askfhefhaldfalfleajkfj new line plese\n");
        printf("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()askfhefhaldfalfleajkfj new line plese\n");
        printf("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()askfhefhaldfalfleajkfj new line plese\n");

	// Paging tests
	setup_paging();
	printf("Paging Enabled");
}
