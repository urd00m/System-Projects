#include <capstone/capstone.h>

// Basic x86 instruction, add %edx,%eax
#define BASIC_INST "\x01\xd0"

// Capstone handler
static csh handle;

// Main function
int main(void) {
	printf("Start test\n");

	// cs_insn stores capstone disasm information
	cs_insn *inst;

	// open capstone 
	int status = cs_open(CS_ARCH_X86, CS_MODE_64, &handle); 
	if(status != CS_ERR_OK) {
		printf("Failed capstone open\n");
		return -1;
	}

	// Run disasm
	size_t count = cs_disasm(handle,BASIC_INST,2,0x1000,1,&inst);
	if(count <= 0) {
		printf("Unable to dissassemble code\n");
		return -1;
	}

	// get information
	printf("mnemonic %s\n", inst->mnemonic);
	printf("operands %s\n", inst->op_str);

	// close handler
	cs_close(&handle);

	return 0;
}
