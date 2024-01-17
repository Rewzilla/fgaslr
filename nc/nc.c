
#include "../src/fgaslr.h"

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_MAIN), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define _main(a, b) ((int (*)(int,char *[]))funcs[0].addr)(a, b)

int main(int argc, char *argv[]) {

	init();

	fgaslr_resolve(funcs);

	ASM_BREAKPOINT();

	_main(argc, argv);

//	ASM_EXIT();

}