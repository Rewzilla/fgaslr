
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_INIT64), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_T64D), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_T64E), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define init64() ((void (*)())funcs[0].addr)()
#define t64d (((uchar *)funcs[1].addr))
#define t64e (((char *)funcs[2].addr))

int
dec64(uchar *out, char *in, int n)
{
	ulong b24;
	uchar *start = out;
	int i, c;

	if(t64e[0] == 0)
		init64();

	b24 = 0;
	i = 0;
	while(n-- > 0){
		c = t64d[*in++];
		if(c == 255)
			continue;
		switch(i){
		case 0:
			b24 = c<<18;
			break;
		case 1:
			b24 |= c<<12;
			break;
		case 2:
			b24 |= c<<6;
			break;
		case 3:
			b24 |= c;
			*out++ = b24>>16;
			*out++ = b24>>8;
			*out++ = b24;
			i = -1;
			break;
		}
		i++;
	}
	switch(i){
	case 2:
		*out++ = b24>>16;
		break;
	case 3:
		*out++ = b24>>16;
		*out++ = b24>>8;
		break;
	}
	*out = 0;
	return out - start;
}
