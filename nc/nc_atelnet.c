
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_WRITE), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define write(a,b,c) ((ssize_t (*)(int,const void *,size_t))funcs[0].addr)(a,b,c)

#ifdef TELNET

/* atelnet :
   Answer anything that looks like telnet negotiation with don't/won't.
   This doesn't modify any data buffers, update the global output count,
   or show up in a hexdump -- it just shits into the outgoing stream.
   Idea and codebase from Mudge@l0pht.com. */
void atelnet (buf, size)
  unsigned char * buf;		/* has to be unsigned here! */
  unsigned int size;
{
  static unsigned char obuf [4];  /* tiny thing to build responses into */
  register int x;
  register unsigned char y;
  register unsigned char * p;

  y = 0;
  p = buf;
  x = size;
  while (x > 0) {
    if (*p != 255)			/* IAC? */
      goto notiac;
    obuf[0] = 255;
    p++; x--;
    if ((*p == 251) || (*p == 252))	/* WILL or WONT */
      y = 254;				/* -> DONT */
    if ((*p == 253) || (*p == 254))	/* DO or DONT */
      y = 252;				/* -> WONT */
    if (y) {
      obuf[1] = y;
      p++; x--;
      obuf[2] = *p;			/* copy actual option byte */
      (void) write (netfd, obuf, 3);
/* if one wanted to bump wrote_net or do a hexdump line, here's the place */
      y = 0;
    } /* if y */
notiac:
    p++; x--;
  } /* while x */
} /* atelnet */
#endif /* TELNET */
