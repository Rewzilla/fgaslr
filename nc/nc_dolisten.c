
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC___ERRNO_LOCATION), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_UDPMODE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_LISTEN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETSOCKNAME), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_LCLEND), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCPY), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BIGBUF_NET), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCAT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_INET_NTOA), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_NTOHS), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_ARM), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_WAIT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC__SETJMP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_JBUF), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_REMEND), NULL},
	// These are necessary for the Debug() macro
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FFLUSH), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDOUT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CONNECT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ACCEPT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_OPTBUF), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HMALLOC), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETSOCKOPT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMSET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GETHOSTPOOP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_NFLAG), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMCMP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DOCONNECT), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define __errno_location() ((int *(*)())funcs[6].addr)()
#define o_udpmode (*(USHORT *)funcs[1].addr)
#define bail(...) ((void (*)(char *,...))funcs[2].addr)(__VA_ARGS__)
#define listen(a,b) ((int (*)(int,int))funcs[3].addr)(a,b)
#define o_verbose (*(USHORT *)funcs[4].addr)
#define getsockname(a,b,c) ((int (*)(int,struct sockaddr *,socklen_t *))funcs[5].addr)(a,b,c)
#define lclend (*(SAI **)funcs[6].addr)
#define holler(...) ((void (*)(char *,...))funcs[7].addr)(__VA_ARGS__)
#define strcpy(a,b) ((char * (*)(char *,const char *))funcs[8].addr)(a,b)
#define bigbuf_net (*(char **)funcs[9].addr)
#define strcat(a,b) ((char * (*)(char *,const char *))funcs[10].addr)(a,b)
#define inet_ntoa(a) ((char * (*)(struct in_addr))funcs[11].addr)(a)
#define ntohs(a) ((uint16_t (*)(uint16_t))funcs[12].addr)(a)
#define arm(a,b) ((void (*)(unsigned int,unsigned int))funcs[13].addr)(a,b)
#define o_wait (*(unsigned int *)funcs[14].addr)
#define _setjmp(a) ((int (*)(struct __jmp_buf_tag __env[1]))funcs[15].addr)(a)
#define jbuf (*(jmp_buf *)funcs[16].addr)
#define recvfrom(a,b,c,d,e,f) ((ssize_t (*)(int,void *,size_t,int,struct sockaddr *,socklen_t *))funcs[17].addr)(a,b,c,d,e,f)
#define remend (*(SAI **)funcs[18].addr)
#define printf(...) ((int (*)(const char *,...))funcs[19].addr)(a, __VA_ARGS__)
#define fflush(a) ((int (*)(FILE *))funcs[20].addr)(a)
#undef stdout
#define stdout (*(FILE **)funcs[21].addr)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[22].addr)(a)
#define connect(a,b,c) ((int (*)(int,const struct sockaddr *,socklen_t))funcs[23].addr)(a,b,c)
#define accept(a,b,c) ((int (*)(int,struct sockaddr *,socklen_t *))funcs[24].addr)(a,b,c)
#define close(a) ((int (*)(int))funcs[25].addr)(a)
#define optbuf (*(char **)funcs[26].addr)
#define Hmalloc(a) ((char * (*)(unsigned int))funcs[27].addr)(a)
#define setsockopt(a,b,c,d,e) ((int (*)(int,int,int,void *,socklen_t))funcs[28].addr)(a,b,c,d,e)
#define memset(a,b,c) ((void * (*)(void *,int,size_t))funcs[29].addr)(a,b,c)
#define gethostpoop(a,b) ((HINF * (*)(char *,USHORT))funcs[30].addr)(a,b)
#define o_nflag (*(USHORT *)funcs[31].addr)
#define memcmp(a,b,c) ((int (*)(const void *,const void *,size_t))funcs[32].addr)(a,b,c)
#define doconnect(a,b,c,d) ((int (*)(IA *,USHORT,IA *,USHORT))funcs[33].addr)(a,b,c,d)

/* dolisten :
   just like doconnect, and in fact calls a hunk of doconnect, but listens for
   incoming and returns an open connection *from* someplace.  If we were
   given host/port args, any connections from elsewhere are rejected.  This
   in conjunction with local-address binding should limit things nicely... */
int dolisten (rad, rp, lad, lp)
  IA * rad;
  USHORT rp;
  IA * lad;
  USHORT lp;
{
  register int nnetfd;
  register int rr;
  HINF * whozis = NULL;
  unsigned int x;		// PATCH
  char * cp;
  USHORT z;
  errno = 0;

/* Pass everything off to doconnect, who in o_listen mode just gets a socket */
  nnetfd = doconnect (rad, rp, lad, lp);
  if (nnetfd <= 0)
    return (-1);
  if (o_udpmode) {			/* apparently UDP can listen ON */
    if (! lp)				/* "port 0",  but that's not useful */
      bail ("UDP listen needs -p arg");
  } else {
    rr = listen (nnetfd, 1);		/* gotta listen() before we can get */
    if (rr < 0)				/* our local random port.  sheesh. */
      bail ("local listen fuxored");
  }

/* Various things that follow temporarily trash bigbuf_net, which might contain
   a copy of any recvfrom()ed packet, but we'll read() another copy later. */

/* I can't believe I have to do all this to get my own goddamn bound address
   and port number.  It should just get filled in during bind() or something.
   All this is only useful if we didn't say -p for listening, since if we
   said -p we *know* what port we're listening on.  At any rate we won't bother
   with it all unless we wanted to see it, although listening quietly on a
   random unknown port is probably not very useful without "netstat". */
  if (o_verbose) {
    x = sizeof (SA);		/* how 'bout getsockNUM instead, pinheads?! */
    rr = getsockname (nnetfd, (SA *) lclend, &x);
    if (rr < 0)
      holler ("local getsockname failed");
    strcpy (bigbuf_net, "listening on [");	/* buffer reuse... */
    if (lclend->sin_addr.s_addr)
      strcat (bigbuf_net, inet_ntoa (lclend->sin_addr));
    else
      strcat (bigbuf_net, "any");
    strcat (bigbuf_net, "] %d ...");
    z = ntohs (lclend->sin_port);
    holler (bigbuf_net, z);
  } /* verbose -- whew!! */

/* UDP is a speeeeecial case -- we have to do I/O *and* get the calling
   party's particulars all at once, listen() and accept() don't apply.
   At least in the BSD universe, however, recvfrom/PEEK is enough to tell
   us something came in, and we can set things up so straight read/write
   actually does work after all.  Yow.  YMMV on strange platforms!  */
  if (o_udpmode) {
    x = sizeof (SA);		/* retval for recvfrom */
    arm (2, o_wait);		/* might as well timeout this, too */
    if (setjmp (jbuf) == 0) {	/* do timeout for initial connect */
      rr = recvfrom		/* and here we block... */
	(nnetfd, bigbuf_net, BIGSIZ, MSG_PEEK, (SA *) remend, &x);
Debug (("dolisten/recvfrom ding, rr = %d, netbuf %s ", rr, bigbuf_net))
    } else
      goto dol_tmo;		/* timeout */
    arm (0, 0);
/* I'm not completely clear on how this works -- BSD seems to make UDP
   just magically work in a connect()ed context, but we'll undoubtedly run
   into systems this deal doesn't work on.  For now, we apparently have to
   issue a connect() on our just-tickled socket so we can write() back.
   Again, why the fuck doesn't it just get filled in and taken care of?!
   This hack is anything but optimal.  Basically, if you want your listener
   to also be able to send data back, you need this connect() line, which
   also has the side effect that now anything from a different source or even a
   different port on the other end won't show up and will cause ICMP errors.
   I guess that's what they meant by "connect".
   Let's try to remember what the "U" is *really* for, eh? */
    rr = connect (nnetfd, (SA *)remend, sizeof (SA));
    goto whoisit;
  } /* o_udpmode */

/* fall here for TCP */
  x = sizeof (SA);		/* retval for accept */
  arm (2, o_wait);		/* wrap this in a timer, too; 0 = forever */
  if (setjmp (jbuf) == 0) {
    rr = accept (nnetfd, (SA *)remend, &x);
  } else
    goto dol_tmo;		/* timeout */
  arm (0, 0);
  close (nnetfd);		/* dump the old socket */
  nnetfd = rr;			/* here's our new one */

whoisit:
  if (rr < 0)
    goto dol_err;		/* bail out if any errors so far */

/* If we can, look for any IP options.  Useful for testing the receiving end of
   such things, and is a good exercise in dealing with it.  We do this before
   the connect message, to ensure that the connect msg is uniformly the LAST
   thing to emerge after all the intervening crud.  Doesn't work for UDP on
   any machines I've tested, but feel free to surprise me. */
#ifdef IP_OPTIONS
  if (! o_verbose)			/* if we wont see it, we dont care */
    goto dol_noop;
  optbuf = Hmalloc (40);
  x = 40;
  rr = getsockopt (nnetfd, IPPROTO_IP, IP_OPTIONS, optbuf, &x);
  if (rr < 0)
    holler ("getsockopt failed");
Debug (("ipoptions ret len %d", x))
  if (x) {				/* we've got options, lessee em... */
    unsigned char * q = (unsigned char *) optbuf;
    char * p = bigbuf_net;		/* local variables, yuk! */
    char * pp = &bigbuf_net[128];	/* get random space farther out... */
    memset (bigbuf_net, 0, 256);	/* clear it all first */
    while (x > 0) {
	sprintf (pp, "%2.2x ", *q);	/* clumsy, but works: turn into hex */
	strcat (p, pp);			/* and build the final string */
	q++; p++;
	x--;
    }
    holler ("IP options: %s", bigbuf_net);
  } /* if x, i.e. any options */
dol_noop:
#endif /* IP_OPTIONS */

/* find out what address the connection was *to* on our end, in case we're
   doing a listen-on-any on a multihomed machine.  This allows one to
   offer different services via different alias addresses, such as the
   "virtual web site" hack. */
  memset (bigbuf_net, 0, 64);
  cp = &bigbuf_net[32];
  x = sizeof (SA);
  rr = getsockname (nnetfd, (SA *) lclend, &x);
  if (rr < 0)
    holler ("post-rcv getsockname failed");
  strcpy (cp, inet_ntoa (lclend->sin_addr));

/* now check out who it is.  We don't care about mismatched DNS names here,
   but any ADDR and PORT we specified had better fucking well match the caller.
   Converting from addr to inet_ntoa and back again is a bit of a kludge, but
   gethostpoop wants a string and there's much gnarlier code out there already,
   so I don't feel bad.
   The *real* question is why BFD sockets wasn't designed to allow listens for
   connections *from* specific hosts/ports, instead of requiring the caller to
   accept the connection and then reject undesireable ones by closing.  In
   other words, we need a TCP MSG_PEEK. */
  z = ntohs (remend->sin_port);
  strcpy (bigbuf_net, inet_ntoa (remend->sin_addr));
  whozis = gethostpoop (bigbuf_net, o_nflag);
  errno = 0;
  x = 0;				/* use as a flag... */
  if (rad)	/* xxx: fix to go down the *list* if we have one? */
    if (memcmp (rad, whozis->iaddrs, sizeof (SA)))
      x = 1;
  if (rp)
    if (z != rp)
      x = 1;
  if (x)					/* guilty! */
    bail ("invalid connection to [%s] from %s [%s] %d",
	cp, whozis->name, whozis->addrs[0], z);
  holler ("connect to [%s] from %s [%s] %d",		/* oh, you're okay.. */
	cp, whozis->name, whozis->addrs[0], z);
  return (nnetfd);				/* open! */

dol_tmo:
  errno = ETIMEDOUT;			/* fake it */
dol_err:
  close (nnetfd);
  return (-1);
} /* dolisten */
