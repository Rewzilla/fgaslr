
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_T64D), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_T64E), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMSET), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define FGASLR_T64D ((uchar *)funcs[0].addr)
#define FGASLR_T64E ((uchar *)funcs[1].addr)
#define FGASLR_MEMSET(a, b, c) ((void * (*)(void *,int, size_t))funcs[2].addr)(a, b, c)

static void
init64(void)
{
	int c, i;

	FGASLR_MEMSET(FGASLR_T64D, 255, 256);
	FGASLR_MEMSET(FGASLR_T64E, '=', 64);
	i = 0;
	for(c = 'A'; c <= 'Z'; c++){
		FGASLR_T64E[i] = c;
		FGASLR_T64D[c] = i++;
	}
	for(c = 'a'; c <= 'z'; c++){
		FGASLR_T64E[i] = c;
		FGASLR_T64D[c] = i++;
	}
	for(c = '0'; c <= '9'; c++){
		FGASLR_T64E[i] = c;
		FGASLR_T64D[c] = i++;
	}
	FGASLR_T64E[i] = '+';
	FGASLR_T64D['+'] = i++;
	FGASLR_T64E[i] = '/';
	FGASLR_T64D['/'] = i;
}
