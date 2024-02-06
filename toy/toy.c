
#include "../src/fgaslr.h"

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_MAIN), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define _main(a, b, c) ((int (*)(int,char *[],char *[]))funcs[0].addr)(a, b, c)

int main(int argc, char *argv[], char *envp[]) {

	fgaslr_init("start", funcs);

//	ASM_BREAKPOINT();

#ifdef ENABLE_UNMAP_IMAGE
	run(funcs[0].addr, argc, argv, envp);
#else
	_main(argc, argv, envp);
#endif

//	ASM_EXIT();

}