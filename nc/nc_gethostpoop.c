
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_H_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HMALLOC), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCPY), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_UNKNOWN), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_INET_ADDR), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETHOSTBYNAME), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRNCPY), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMCPY), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETHOSTBYADDR), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_COMPAREHOSTS), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define errno (*(int *)funcs[0].addr)
#define h_errno (*(int *)funcs[1].addr)
#define Hmalloc(a) ((char * (*)(unsigned int))funcs[2].addr)(a)
#define bail(a,b,c,d,e,f,g) ((void (*)(char *,char *,char *,char *,char *,char *,char *,))funcs[3].addr)(a,b,c,d,e,f,g)
#define strcpy(a,b) ((char * (*)(char *,const char *))funcs[4].addr)(a,b)
#define unknown ((static char *)funcs[5].addr)
#define inet_addr(a) ((inet_addr_t (*)(const char *))funcs[6].addr)(a)
#define gethostbyname(a) ((struct hostent * (*)(const char *))funcs[7].addr)(a)
#define strncpy(a,b,c) ((char * (*)(char *,const char *,size_t))funcs[8].addr)(a,b,c)
#define memcpy(a,b,c) ((void * (*)(void *,const void *,size_t))funcs[9].addr)(a,b,c)
#define o_verbose (*(USHORT *)funcs[10].addr)
#define gethostbyname(a,b,b) ((struct hostent * (*)(const void *,socklen_t,int))funcs[11].addr)(a,b,c)
#define holler(a,b,c,d,e,f,g) ((void (*)(char *,char *,char *,char *,char *,char *,char *,))funcs[12].addr)(a,b,c,d,e,f,g)
#define comparehosts(a,b) ((int (*)(HINF *,struct hostent *))funcs[13].addr)(a,b)

/* gethostpoop :
   resolve a host 8 ways from sunday; return a new host_poop struct with its
   info.  The argument can be a name or [ascii] IP address; it will try its
   damndest to deal with it.  "numeric" governs whether we do any DNS at all,
   and we also check o_verbose for what's appropriate work to do. */
HINF * gethostpoop (name, numeric)
  char * name;
  USHORT numeric;
{
  struct hostent * hostent;
  struct in_addr iaddr;
  register HINF * poop = NULL;
  register int x;

/* I really want to strangle the twit who dreamed up all these sockaddr and
   hostent abstractions, and then forced them all to be incompatible with
   each other so you *HAVE* to do all this ridiculous casting back and forth.
   If that wasn't bad enough, all the doc insists on referring to local ports
   and addresses as "names", which makes NO sense down at the bare metal.

   What an absolutely horrid paradigm, and to think of all the people who
   have been wasting significant amounts of time fighting with this stupid
   deliberate obfuscation over the last 10 years... then again, I like
   languages wherein a pointer is a pointer, what you put there is your own
   business, the compiler stays out of your face, and sheep are nervous.
   Maybe that's why my C code reads like assembler half the time... */

/* If we want to see all the DNS stuff, do the following hair --
   if inet_addr, do reverse and forward with any warnings; otherwise try
   to do forward and reverse with any warnings.  In other words, as long
   as we're here, do a complete DNS check on these clowns.  Yes, it slows
   things down a bit for a first run, but once it's cached, who cares? */

  errno = 0;
  h_errno = 0;
  if (name)
    poop = (HINF *) Hmalloc (sizeof (HINF));
  if (! poop)
    bail ("gethostpoop fuxored");
  strcpy (poop->name, unknown);		/* preload it */
/* see wzv:workarounds.c for dg/ux return-a-struct inet_addr lossage */
  iaddr.s_addr = inet_addr (name);

  if (iaddr.s_addr == INADDR_NONE) {	/* here's the great split: names... */
    if (numeric)
      bail ("Can't parse %s as an IP address", name);
    hostent = gethostbyname (name);
    if (! hostent)
/* failure to look up a name is fatal, since we can't do anything with it */
      bail ("%s: forward host lookup failed: ", name);
    strncpy (poop->name, hostent->h_name, MAXHOSTNAMELEN - 2);
    for (x = 0; hostent->h_addr_list[x] && (x < 8); x++) {
      memcpy (&poop->iaddrs[x], hostent->h_addr_list[x], sizeof (IA));
      strncpy (poop->addrs[x], inet_ntoa (poop->iaddrs[x]),
	sizeof (poop->addrs[0]));
    } /* for x -> addrs, part A */
    if (! o_verbose)			/* if we didn't want to see the */
      return (poop);			/* inverse stuff, we're done. */
/* do inverse lookups in separate loop based on our collected forward addrs,
   since gethostby* tends to crap into the same buffer over and over */
    for (x = 0; poop->iaddrs[x].s_addr && (x < 8); x++) {
      hostent = gethostbyaddr ((char *)&poop->iaddrs[x],
				sizeof (IA), AF_INET);
      if ((! hostent) || (! hostent-> h_name))
	holler ("Warning: inverse host lookup failed for %s: ",
	  poop->addrs[x]);
      else
	(void) comparehosts (poop, hostent);
    } /* for x -> addrs, part B */

  } else {  /* not INADDR_NONE: numeric addresses... */
    memcpy (poop->iaddrs, &iaddr, sizeof (IA));
    strncpy (poop->addrs[0], inet_ntoa (iaddr), sizeof (poop->addrs));
    if (numeric)			/* if numeric-only, we're done */
      return (poop);
    if (! o_verbose)			/* likewise if we don't want */
      return (poop);			/* the full DNS hair */
    hostent = gethostbyaddr ((char *) &iaddr, sizeof (IA), AF_INET);
/* numeric or not, failure to look up a PTR is *not* considered fatal */
    if (! hostent)
	holler ("%s: inverse host lookup failed: ", name);
    else {
	strncpy (poop->name, hostent->h_name, MAXHOSTNAMELEN - 2);
	hostent = gethostbyname (poop->name);
	if ((! hostent) || (! hostent->h_addr_list[0]))
	  holler ("Warning: forward host lookup failed for %s: ",
		poop->name);
	else
	  (void) comparehosts (poop, hostent);
    } /* if hostent */
  } /* INADDR_NONE Great Split */

/* whatever-all went down previously, we should now have a host_poop struct
   with at least one IP address in it. */
  h_errno = 0;
  return (poop);
} /* gethostpoop */
