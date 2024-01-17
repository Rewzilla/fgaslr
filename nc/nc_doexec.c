
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
	{FGASLR_ENTRY(LIB_LIBC, FUNC_DUP2), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRRCHR), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_PR00GIE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_EXECL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define printf(...) ((int (*)(const char *,...))funcs[0].addr)(a, __VA_ARGS__)
#define fflush(a) ((int (*)(FILE *))funcs[1].addr)(a)
#define stdout (*(FILE **)funcs[2].addr)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[3].addr)(a)
#define dup2(a,b) ((int (*)(int,int))funcs[4].addr)(a,b)
#define close(a) ((int (*)(int))funcs[5].addr)(a)
#define strrchr(a,b) ((char * (*)(const char *,int))funcs[6].addr)(a,b)
#define pr00gie (*(char **)funcs[7].addr)
#define execl(a,b,...) ((int (*)(const char *,const char *,...))funcs[8].addr)(a,b,__VA_ARGS__)
#define bail(...) ((void (*)(char *,...))funcs[9].addr)(__VA_ARGS__)

#ifdef GAPING_SECURITY_HOLE
/* doexec :
   fiddle all the file descriptors around, and hand off to another prog.  Sort
   of like a one-off "poor man's inetd".  This is the only section of code
   that would be security-critical, which is why it's ifdefed out by default.
   Use at your own hairy risk; if you leave shells lying around behind open
   listening ports you deserve to lose!! */
doexec (fd)
  int fd;
{
  register char * p;

  dup2 (fd, 0);				/* the precise order of fiddlage */
  close (fd);				/* is apparently crucial; this is */
  dup2 (0, 1);				/* swiped directly out of "inetd". */
  dup2 (0, 2);
  p = strrchr (pr00gie, '/');		/* shorter argv[0] */
  if (p)
    p++;
  else
    p = pr00gie;
Debug (("gonna exec %s as %s...", pr00gie, p))
  execl (pr00gie, p, NULL);
  bail ("exec %s failed", pr00gie);	/* this gets sent out.  Hmm... */
} /* doexec */
#endif /* GAPING_SECURITY_HOLE */
