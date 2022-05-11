#include <stdlib.h>
#include "urd00m_output.h"

int main(void) {
	INFO("Beginning call_malloc\n");
	char * alloc = (char *) malloc(0x100);
	if(alloc == 0) {
		FATAL("Malloc failed!\n");
		return -1;
	}

	// Just to see what it is before we copy stuff to it 
	WARN("Alloc has value %s before strncpy\n");

	// Assign item to alloc
	strncpy(alloc, "Copy complete!", 14);

	// Output
	INFO("Finished alloc, alloc has value: %s\n", alloc);
	return 0;
}
