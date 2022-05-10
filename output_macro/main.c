#include <stdio.h>
#include "urd00m_output.h"

int main(void) {
	printf("Simple output\n");

	INFO("My output %d\n", 12321);
	WARN("My warning %d\n", 13213);
	ERROR("My error %d\n", 24324);
	FATAL("My fatal %d\n", 234234);
	return 0;
}
