
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_UDPMODE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_P_TCP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_P_UDP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_PORTPOOP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_NFLAG), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_HTONS), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETSERVBYPORT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_NTOHS), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRNCPY), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ATOI), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETSERVBYNAME), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SPRINTF), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_UDPMODE), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define o_verbose (*(USHORT *)funcs[0].addr)
#define p_tcp ((char *)funcs[1].addr)
#define p_udp ((char *)funcs[2].addr)
#define portpoop (*(PINF **)funcs[3].addr)
#define o_nflag (*(USHORT *)funcs[4].addr)
#define htons(a) ((uint16_t (*)(uint16_t))funcs[5].addr)(a)
#define getservbyport(a,b) ((struct servent * (*)(int,const char *))funcs[6].addr)(a,b)
#define ntohs(a) ((uint16_t (*)(uint16_t))funcs[7].addr)(a)
#define holler(...) ((void (*)(char *,...))funcs[8].addr)(__VA_ARGS__)
#define strncpy(a,b,c) ((char * (*)(char *,const char *,size_t))funcs[9].addr)(a,b,c)
#define atoi(a) ((int (*)(const char *))funcs[10].addr)(a)
#define getservbyname(a,b) ((struct servent * (*)(const char *,const char *))funcs[11].addr)(a,b)
#define sprintf(a,...) ((int (*)(char *,...))funcs[12].addr)(a,__VA_ARGS__)
#define o_udpmode (*(USHORT *)funcs[13].addr)

/* getportpoop :
   Same general idea as gethostpoop -- look up a port in /etc/services, fill
   in global port_poop, but return the actual port *number*.  Pass ONE of:
	pstring to resolve stuff like "23" or "exec";
	pnum to reverse-resolve something that's already a number.
   If o_nflag is on, fill in what we can but skip the getservby??? stuff.
   Might as well have consistent behavior here, and it *is* faster. */
USHORT getportpoop (pstring, pnum)
  char * pstring;
  unsigned int pnum;
{
  struct servent * servent;
  register int x;
  register int y;
  char * whichp = p_tcp;
  if (o_udpmode)
    whichp = p_udp;
  portpoop->name[0] = '?';		/* fast preload */
  portpoop->name[1] = '\0';

/* case 1: reverse-lookup of a number; placed first since this case is much
   more frequent if we're scanning */
  if (pnum) {
    if (pstring)			/* one or the other, pleeze */
      return (0);
    x = pnum;
    if (o_nflag)			/* go faster, skip getservbyblah */
      goto gp_finish;
    y = htons (x);			/* gotta do this -- see Fig.1 below */
    servent = getservbyport (y, whichp);
    if (servent) {
      y = ntohs (servent->s_port);
      if (x != y)			/* "never happen" */
	holler ("Warning: port-bynum mismatch, %d != %d", x, y);
      strncpy (portpoop->name, servent->s_name, sizeof (portpoop->name));
    } /* if servent */
    goto gp_finish;
  } /* if pnum */

/* case 2: resolve a string, but we still give preference to numbers instead
   of trying to resolve conflicts.  None of the entries in *my* extensive
   /etc/services begins with a digit, so this should "always work" unless
   you're at 3com and have some company-internal services defined... */
  if (pstring) {
    if (pnum)				/* one or the other, pleeze */
      return (0);
    x = atoi (pstring);
    if (x)
      return (getportpoop (NULL, x));	/* recurse for numeric-string-arg */
    if (o_nflag)			/* can't use names! */
      return (0);
    servent = getservbyname (pstring, whichp);
    if (servent) {
      strncpy (portpoop->name, servent->s_name, sizeof (portpoop->name));
      x = ntohs (servent->s_port);
      goto gp_finish;
    } /* if servent */
  } /* if pstring */

  return (0);				/* catches any problems so far */

/* Obligatory netdb.h-inspired rant: servent.s_port is supposed to be an int.
   Despite this, we still have to treat it as a short when copying it around.
   Not only that, but we have to convert it *back* into net order for
   getservbyport to work.  Manpages generally aren't clear on all this, but
   there are plenty of examples in which it is just quietly done.  More BSD
   lossage... since everything getserv* ever deals with is local to our own
   host, why bother with all this network-order/host-order crap at all?!
   That should be saved for when we want to actually plug the port[s] into
   some real network calls -- and guess what, we have to *re*-convert at that
   point as well.  Fuckheads. */

gp_finish:
/* Fall here whether or not we have a valid servent at this point, with
   x containing our [host-order and therefore useful, dammit] port number */
  sprintf (portpoop->anum, "%d", x);	/* always load any numeric specs! */
  portpoop->num = (x & 0xffff);		/* ushort, remember... */
  return (portpoop->num);
} /* getportpoop */
