
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#ifdef GAPING_SECURITY_HOLE
char * pr00gie = NULL;
#endif /* GAPING_SECURITY_HOLE */
