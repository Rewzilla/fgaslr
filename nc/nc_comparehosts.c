
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_H_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCMP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCASECMP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define errno (*(int *)funcs[0].addr)
#define h_errno (*(int *)funcs[1].addr)
#define strcmp(a,b) ((int (*)(const char *,const char *))funcs[2].addr)(a,b)
#define strcasecmp(a,b) ((int (*)(const char *,const char *))funcs[3].addr)(a,b)
#define holler(...) ((void (*)(char *,...))funcs[4].addr)(__VA_ARGS__)

/* comparehosts :
   cross-check the host_poop we have so far against new gethostby*() info,
   and holler about mismatches.  Perhaps gratuitous, but it can't hurt to
   point out when someone's DNS is fukt.  Returns 1 if mismatch, in case
   someone else wants to do something about it. */
int comparehosts (poop, hp)
  HINF * poop;
  struct hostent * hp;
{
  errno = 0;
  h_errno = 0;
/* The DNS spec is officially case-insensitive, but for those times when you
   *really* wanna see any and all discrepancies, by all means define this. */
#ifdef ANAL			
  if (strcmp (poop->name, hp->h_name) != 0) {		/* case-sensitive */
#else
  if (strcasecmp (poop->name, hp->h_name) != 0) {	/* normal */
#endif
    holler ("DNS fwd/rev mismatch: %s != %s", poop->name, hp->h_name);
    return (1);
  }
  return (0);
/* ... do we need to do anything over and above that?? */
} /* comparehosts */
