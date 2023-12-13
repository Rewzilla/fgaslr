
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

#define t64d ((uchar *)funcs[0].addr)
#define t64e ((uchar *)funcs[1].addr)
#define memset(a, b, c) ((void * (*)(void *,int, size_t))funcs[2].addr)(a, b, c)

static void
init64(void)
{
	int c, i;

	memset(t64d, 255, 256);
	memset(t64e, '=', 64);
	i = 0;
	for(c = 'A'; c <= 'Z'; c++){
		t64e[i] = c;
		t64d[c] = i++;
	}
	for(c = 'a'; c <= 'z'; c++){
		t64e[i] = c;
		t64d[c] = i++;
	}
	for(c = '0'; c <= '9'; c++){
		t64e[i] = c;
		t64d[c] = i++;
	}
	t64e[i] = '+';
	t64d['+'] = i++;
	t64e[i] = '/';
	t64d['/'] = i;
}
