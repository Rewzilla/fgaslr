
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_RANDOM), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define random(a) ((long (*)())funcs[0].addr)(a)

/* nextport :
   Come up with the next port to try, be it random or whatever.  "block" is
   a ptr to randports array, whose bytes [so far] carry these meanings:
	0	ignore
	1	to be tested
	2	tested [which is set as we find them here]
   returns a USHORT random port, or 0 if all the t-b-t ones are used up. */
USHORT nextport (block)
  char * block;
{
  register unsigned int x;
  register unsigned int y;

  y = 70000;			/* high safety count for rnd-tries */
  while (y > 0) {
    x = (RAND() & 0xffff);
    if (block[x] == 1) {	/* try to find a not-done one... */
      block[x] = 2;
      break;
    }
    x = 0;			/* bummer. */
    y--;
  } /* while y */
  if (x)
    return (x);

  y = 65535;			/* no random one, try linear downsearch */
  while (y > 0) {		/* if they're all used, we *must* be sure! */
    if (block[y] == 1) {
      block[y] = 2;
      break;
    }
    y--;
  } /* while y */
  if (y)
    return (y);			/* at least one left */

  return (0);			/* no more left! */
} /* nextport */
