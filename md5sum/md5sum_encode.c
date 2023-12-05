
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

/*
 *	encodes input (uint) into output (byte). Assumes len is
 *	a multiple of 4.
 */
void
encode(byte *output, uint *input, uint len)
{
	uint x;
	byte *e;

	for(e = output + len; output < e;) {
		x = *input++;
		*output++ = x;
		*output++ = x >> 8;
		*output++ = x >> 16;
		*output++ = x >> 24;
	}
}
