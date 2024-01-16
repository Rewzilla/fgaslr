
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define bail(a,b,c,d,e,f,g) ((void (*)(char *,char *,char *,char *,char *,char *,char *,))funcs[0].addr)(a,b,c,d,e,f,g)

/* loadports :
   set "to be tested" indications in BLOCK, from LO to HI.  Almost too small
   to be a separate routine, but makes main() a little cleaner... */
void loadports (block, lo, hi)
  char * block;
  USHORT lo;
  USHORT hi;
{
  USHORT x;

  if (! block)
    bail ("loadports: no block?!");
  if ((! lo) || (! hi))
    bail ("loadports: bogus values %d, %d", lo, hi);
  x = hi;
  while (lo <= x) {
    block[x] = 1;
    x--;
  }
} /* loadports */
