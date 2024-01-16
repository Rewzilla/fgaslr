
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_OFD), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_STAGE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_OUT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_NET), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SPRINTF), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HEXNIBS), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_WRITE), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define ofd (*(int *)funcs[0].addr)
#define bail(a,b,c,d,e,f,g) ((void (*)(char *,char *,char *,char *,char *,char *,char *,))funcs[1].addr)(a,b,c,d,e,f,g)
#define stage (*(unsigned char **)funcs[2].addr)
#define wrote_out (*(int *)funcs[3].addr)
#define wrote_net (*(int *)funcs[4].addr)
#define sprintf(a,...) ((int (*)(char *,...))funcs[5].addr)(a,__VA_ARGS__)
#define hexnibs ((static char *)funcs[6].addr)
#define write(a,b,c) ((ssize_t (*)(int,const void *,size_t))funcs[7].addr)(a,b,c)

/* oprint :
   Hexdump bytes shoveled either way to a running logfile, in the format:
D offset       -  - - - --- 16 bytes --- - - -  -     # .... ascii .....
   where "which" sets the direction indicator, D:
	0 -- sent to network, or ">"
	1 -- rcvd and printed to stdout, or "<"
   and "buf" and "n" are data-block and length.  If the current block generates
   a partial line, so be it; we *want* that lockstep indication of who sent
   what when.  Adapted from dgaudet's original example -- but must be ripping
   *fast*, since we don't want to be too disk-bound... */
void oprint (which, buf, n)
  int which;
  char * buf;
  int n;
{
  int bc;			/* in buffer count */
  int obc;			/* current "global" offset */
  int soc;			/* stage write count */
  register unsigned char * p;	/* main buf ptr; m.b. unsigned here */
  register unsigned char * op;	/* out hexdump ptr */
  register unsigned char * a;	/* out asc-dump ptr */
  register int x;
  register unsigned int y;

  if (! ofd)
    bail ("oprint called with no open fd?!");
  if (n == 0)
    return;

  op = stage;
  if (which) {
    *op = '<';
    obc = wrote_out;		/* use the globals! */
  } else {
    *op = '>';
    obc = wrote_net;
  }
  op++;				/* preload "direction" */
  *op = ' ';
  p = (unsigned char *) buf;
  bc = n;
  stage[59] = '#';		/* preload separator */
  stage[60] = ' ';

  while (bc) {			/* for chunk-o-data ... */
    x = 16;
    soc = 78;			/* len of whole formatted line */
    if (bc < x) {
      soc = soc - 16 + bc;	/* fiddle for however much is left */
      x = (bc * 3) + 11;	/* 2 digits + space per, after D & offset */
      op = &stage[x];
      x = 16 - bc;
      while (x) {
	*op++ = ' ';		/* preload filler spaces */
	*op++ = ' ';
	*op++ = ' ';
	x--;
      }
      x = bc;			/* re-fix current linecount */
    } /* if bc < x */

    bc -= x;			/* fix wrt current line size */
    sprintf (&stage[2], "%8.8x ", obc);		/* xxx: still slow? */
    obc += x;			/* fix current offset */
    op = &stage[11];		/* where hex starts */
    a = &stage[61];		/* where ascii starts */

    while (x) {			/* for line of dump, however long ... */
      y = (int)(*p >> 4);	/* hi half */
      *op = hexnibs[y];
      op++;
      y = (int)(*p & 0x0f);	/* lo half */
      *op = hexnibs[y];
      op++;
      *op = ' ';
      op++;
      if ((*p > 31) && (*p < 127))
	*a = *p;		/* printing */
      else
	*a = '.';		/* nonprinting, loose def */
      a++;
      p++;
      x--;
    } /* while x */
    *a = '\n';			/* finish the line */
    x = write (ofd, stage, soc);
    if (x < 0)
      bail ("ofd write err");
  } /* while bc */
} /* oprint */
