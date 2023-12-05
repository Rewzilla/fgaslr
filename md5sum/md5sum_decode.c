
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

void
decode(uint *output, byte *input, uint len)
{
	byte *e;

	for(e = input+len; input < e; input += 4)
		*output++ = input[0] | (input[1] << 8) |
			(input[2] << 16) | (input[3] << 24);
}
