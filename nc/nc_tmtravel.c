
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SIGNAL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ALARM), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_LONGJMP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_JVAL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_JBUF), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define signal(a,b) ((sighandler_t (*)(int,sighandler_t))funcs[0].addr)(a,b)
#define alarm(a) ((unsigned int (*)(unsigned int))funcs[1].addr)(a)
#define longjmp(a,b) ((void (*)(jmp_buf,int))funcs[2].addr)(a,b)
#define jval (*(int *)funcs[3].addr)
#define jbuf (*(jmp_buf *)funcs[4].addr)
#define bail(a,b,c,d,e,f,g) ((void (*)(char *,char *,char *,char *,char *,char *,char *,))funcs[5].addr)(a,b,c,d,e,f,g)

/* timeout and other signal handling cruft */
void tmtravel ()
{
  signal (SIGALRM, SIG_IGN);
  alarm (0);
  if (jval == 0)
    bail ("spurious timer interrupt!");
  longjmp (jbuf, jval);
}
