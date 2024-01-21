
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SIGNAL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ALARM), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_JVAL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_TMTRAVEL), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define signal(a,b) ((sighandler_t (*)(int,sighandler_t))funcs[0].addr)(a,b)
#define alarm(a) ((unsigned int (*)(unsigned int))funcs[1].addr)(a)
#define jval (*(int *)funcs[2].addr)
#define tmtravel ((void (*)())funcs[3].addr)

/* arm :
   set the timer.  Zero secs arg means unarm */
void arm (num, secs)
  unsigned int num;
  unsigned int secs;
{
  if (secs == 0) {			/* reset */
    signal (SIGALRM, SIG_IGN);
    alarm (0);
    jval = 0;
  } else {				/* set */
    signal (SIGALRM, tmtravel);
    alarm (secs);
    jval = num;
  } /* if secs */
} /* arm */
