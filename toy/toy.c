
#include "../src/fgaslr.h"

struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_MAIN), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define CALL_MAIN(a, b) ((int (*)(int,char *[]))funcs[0].addr)(a, b);

int main(int argc, char *argv[]) {

	init();

	fgaslr_resolve(funcs);

	ASM_BREAKPOINT();

	CALL_MAIN(argc, argv);

	ASM_EXIT();

}