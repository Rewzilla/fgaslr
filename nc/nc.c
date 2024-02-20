
// source: https://nc110.sourceforge.io/

#include "../src/fgaslr.h"
#include "../src/stats.h"

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_MAIN), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define _main(a, b, c) ((int (*)(int,char *[], char *[]))funcs[0].addr)(a, b, c)

int main(int argc, char *argv[], char *envp[]) {

	fgaslr_init("start", funcs);

//	ASM_BREAKPOINT();

#ifdef ENABLE_RUNTIME_STATS
	timer_start();
#endif

#ifdef ENABLE_UNMAP_IMAGE
	run(funcs[0].addr, argc, argv, envp);
#else
	_main(argc, argv, envp);
#endif

#ifdef ENABLE_RUNTIME_STATS
	timer_end();
	runtime_save();
#endif

//	ASM_EXIT();

}

#ifdef ENABLE_RUNTIME_STATS
// netcat calls exit() sometimes, which will skip stats save
// catch it with a global destructor if needed.
void __attribute__((destructor)) fini() {

	timer_end();
	runtime_save();

}
#endif