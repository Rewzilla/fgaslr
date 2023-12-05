
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_INIT64), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_T64E), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define FGASLR_INIT64() ((void (*)())funcs[0].addr)()
#define FGASLR_T64E ((char *)funcs[1].addr)

int
enc64(char *out, uchar *in, int n)
{
	int i;
	ulong b24;
	char *start = out;

	if(FGASLR_T64E[0] == 0)
		FGASLR_INIT64();
	for(i = n/3; i > 0; i--){
		b24 = (*in++)<<16;
		b24 |= (*in++)<<8;
		b24 |= *in++;
		*out++ = FGASLR_T64E[(b24>>18)];
		*out++ = FGASLR_T64E[(b24>>12)&0x3f];
		*out++ = FGASLR_T64E[(b24>>6)&0x3f];
		*out++ = FGASLR_T64E[(b24)&0x3f];
	}

	switch(n%3){
	case 2:
		b24 = (*in++)<<16;
		b24 |= (*in)<<8;
		*out++ = FGASLR_T64E[(b24>>18)];
		*out++ = FGASLR_T64E[(b24>>12)&0x3f];
		*out++ = FGASLR_T64E[(b24>>6)&0x3f];
		break;
	case 1:
		b24 = (*in)<<16;
		*out++ = FGASLR_T64E[(b24>>18)];
		*out++ = FGASLR_T64E[(b24>>12)&0x3f];
		*out++ = '=';
		break;
	}
	*out++ = '=';
	*out = 0;
	return out - start;
}
