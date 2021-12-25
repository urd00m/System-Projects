#include <stddef.h>
#include <stdint.h>

#include <kernel/paging.h>

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();
extern void breakPaging();

static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void setup_paging() {
	/*
		Page Directory setup 
	*/
	//set each entry to not present
	int i;
	for(i = 0; i < 1024; i++)
	{
		// This sets the following flags to the pages:
		//   Supervisor: Only kernel-mode can access them
		//   Write Enabled: It can be both read from and written to
		//   Not Present: The page table is not present
		page_directory[i] = 0x00000002;
	}

	/*
		Page table setup
	*/
	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	unsigned int j;

	//we will fill all 1024 entries in the table, mapping 4 megabytes
	for(j = 0; j < 1024; j++)
	{
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		first_page_table[j] = (j * 0x1000) | 3; // attributes: supervisor level, read/write, present.
		// NOTE: sets the physical page number (PPN) to increments of 8.
	}

	/*
		Put the first page table into the page table directory
	*/
	page_directory[0] = ((unsigned int)first_page_table) | 3;
//	page_directory[0] = 0xC0000000 | 3; //This will break it

	/*
		Write page table to cr3 and enable paging
	*/
	loadPageDirectory(page_directory);
	enablePaging();
//	breakPaging(); //one way to break paging
//	loadPageDirectory(3); //Another way to break paging (This also confirms that the paging_asm.S functions are doing there jobs
}
