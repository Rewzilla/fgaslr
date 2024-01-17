
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	// These are necessary for the Debug() macro
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FFLUSH), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDOUT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define printf(...) ((int (*)(const char *,...))funcs[0].addr)(a, __VA_ARGS__)
#define fflush(a) ((int (*)(FILE *))funcs[1].addr)(a)
#undef stdout
#define stdout (*(FILE **)funcs[2].addr)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[3].addr)(a)

/* findline :
   find the next newline in a buffer; return inclusive size of that "line",
   or the entire buffer size, so the caller knows how much to then write().
   Not distinguishing \n vs \r\n for the nonce; it just works as is... */
unsigned int findline (buf, siz)
  char * buf;
  unsigned int siz;
{
  register char * p;
  register int x;
  if (! buf)			/* various sanity checks... */
    return (0);
  if (siz > BIGSIZ)
    return (0);
  x = siz;
  for (p = buf; x > 0; x--) {
    if (*p == '\n') {
      x = (int) (p - buf);
      x++;			/* 'sokay if it points just past the end! */
Debug (("findline returning %d", x))
      return (x);
    }
    p++;
  } /* for */
Debug (("findline returning whole thing: %d", siz))
  return (siz);
} /* findline */
