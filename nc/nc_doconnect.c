
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_UDPMODE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SOCKET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SETSOCKOPT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_LCLEND), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_REMEND), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_BIND), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_INET_NTOA), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_LISTEN), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_HTONS), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GATESIDX), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_OPTBUF), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HMALLOC), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GATESPTR), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMCPY), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GATES), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_ARM), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_WAIT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SETJMP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CONNECT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_JBUF), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define o_udpmode (*(USHORT *)funcs[0].addr)
#define socket(a,b,c) ((int (*)(int,int,int))funcs[1].addr)(a,b,c)
#define bail(...) ((void (*)(char *,...))funcs[2].addr)(__VA_ARGS__)
#define setsockopt(a,b,c,d,e) ((int (*)(int,int,int,const void *,socklen_t))funcs[3].addr)(a,b,c,d,e)
#define holler(...) ((void (*)(char *,...))funcs[4].addr)(__VA_ARGS__)
#define lclend (*(SAI **)funcs[5].addr)
#define remend (*(SAI **)funcs[6].addr)
#define bind(a,b,c) ((int (*)(int,const struct sockaddr *,socklen_t))funcs[7].addr)(a,b,c)
#define errno (*(int *)funcs[8].addr)
#define inet_ntoa(a) ((char * (*)(struct in_addr))funcs[9].addr)(a)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[10].addr)(a)
#define o_listen (*(USHORT *)funcs[11].addr)
#define htons(a) ((uint16_t (*)(uint16_t))funcs[12].addr)(a)
#define gatesidx (*(int *)funcs[13].addr)
#define optbuf (*(char **)funcs[14].addr)
#define Hmalloc(a) ((char * (*)(unsigned int))funcs[15].addr)(a)
#define gatesptr (*(int *)funcs[16].addr)
#define memcpy(a,b,c) ((void * (*)(void *,const void *,size_t))funcs[17].addr)(a,b,c)
#define gates (*(HINF ***)funcs[18].addr)
#define arm(a,b) ((void (*)(unsigned int,unsigned int))funcs[19].addr)(a,b)
#define o_wait (*(unsigned int *)funcs[20].addr)
#define setjmp(a) ((int (*)(jmp_buf))funcs[21].addr)(a)
#define connect(a,b,c) ((int (*)(int,const struct sockaddr *,socklen_t))funcs[22].addr)(a,b,c)
#define close(a) ((int (*)(int))funcs[23].addr)(a)
#define jbuf (*(jmp_buf *)funcs[24].addr)

/* doconnect :
   do all the socket stuff, and return an fd for one of
	an open outbound TCP connection
	a UDP stub-socket thingie
   with appropriate socket options set up if we wanted source-routing, or
	an unconnected TCP or UDP socket to listen on.
   Examines various global o_blah flags to figure out what-all to do. */
int doconnect (rad, rp, lad, lp)
  IA * rad;
  USHORT rp;
  IA * lad;
  USHORT lp;
{
  register int nnetfd;
  register int rr;
  int x, y;
  errno = 0;

/* grab a socket; set opts */
newskt:
  if (o_udpmode)
    nnetfd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  else
    nnetfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (nnetfd < 0)
    bail ("Can't get socket");
  if (nnetfd == 0)		/* if stdin was closed this might *be* 0, */
    goto newskt;		/* so grab another.  See text for why... */
  x = 1;
  rr = setsockopt (nnetfd, SOL_SOCKET, SO_REUSEADDR, &x, sizeof (x));
  if (rr == -1)
    holler ("nnetfd reuseaddr failed");		/* ??? */
#ifdef SO_REUSEPORT	/* doesnt exist everywhere... */
  rr = setsockopt (nnetfd, SOL_SOCKET, SO_REUSEPORT, &x, sizeof (x));
  if (rr == -1)
    holler ("nnetfd reuseport failed");		/* ??? */
#endif
#if 0
/* If you want to screw with RCVBUF/SNDBUF, do it here.  Liudvikas Bukys at
   Rochester sent this example, which would involve YET MORE options and is
   just archived here in case you want to mess with it.  o_xxxbuf are global
   integers set in main() getopt loop, and check for rr == 0 afterward. */
  rr = setsockopt(nnetfd, SOL_SOCKET, SO_RCVBUF, &o_rcvbuf, sizeof o_rcvbuf);
  rr = setsockopt(nnetfd, SOL_SOCKET, SO_SNDBUF, &o_sndbuf, sizeof o_sndbuf);
#endif
  
  /* fill in all the right sockaddr crud */
    lclend->sin_family = AF_INET;

/* fill in all the right sockaddr crud */
  lclend->sin_family = AF_INET;
  remend->sin_family = AF_INET;

/* if lad/lp, do appropriate binding */
  if (lad)
    memcpy (&lclend->sin_addr.s_addr, lad, sizeof (IA));
  if (lp)
    lclend->sin_port = htons (lp);
  rr = 0;
  if (lad || lp) {
    x = (int) lp;
/* try a few times for the local bind, a la ftp-data-port... */
    for (y = 4; y > 0; y--) {
      rr = bind (nnetfd, (SA *)lclend, sizeof (SA));
      if (rr == 0)
	break;
      if (errno != EADDRINUSE)
	break;
      else {
	holler ("retrying local %s:%d", inet_ntoa (lclend->sin_addr), lp);
	sleep (2);
	errno = 0;			/* clear from sleep */
      } /* if EADDRINUSE */
    } /* for y counter */
  } /* if lad or lp */
  if (rr)
    bail ("Can't grab %s:%d with bind",
	inet_ntoa(lclend->sin_addr), lp);

  if (o_listen)
    return (nnetfd);			/* thanks, that's all for today */

  memcpy (&remend->sin_addr.s_addr, rad, sizeof (IA));
  remend->sin_port = htons (rp);

/* rough format of LSRR option and explanation of weirdness.
Option comes after IP-hdr dest addr in packet, padded to *4, and ihl > 5.
IHL is multiples of 4, i.e. real len = ip_hl << 2.
	type 131	1	; 0x83: copied, option class 0, number 3
	len		1	; of *whole* option!
	pointer		1	; nxt-hop-addr; 1-relative, not 0-relative
	addrlist...	var	; 4 bytes per hop-addr
	pad-to-32	var	; ones, i.e. "NOP"

If we want to route A -> B via hops C and D, we must add C, D, *and* B to the
options list.  Why?  Because when we hand the kernel A -> B with list C, D, B
the "send shuffle" inside the kernel changes it into A -> C with list D, B and
the outbound packet gets sent to C.  If B wasn't also in the hops list, the
final destination would have been lost at this point.

When C gets the packet, it changes it to A -> D with list C', B where C' is
the interface address that C used to forward the packet.  This "records" the
route hop from B's point of view, i.e. which address points "toward" B.  This
is to make B better able to return the packets.  The pointer gets bumped by 4,
so that D does the right thing instead of trying to forward back to C.

When B finally gets the packet, it sees that the pointer is at the end of the
LSRR list and is thus "completed".  B will then try to use the packet instead
of forwarding it, i.e. deliver it up to some application.

Note that by moving the pointer yourself, you could send the traffic directly
to B but have it return via your preconstructed source-route.  Playing with
this and watching "tcpdump -v" is the best way to understand what's going on.

Only works for TCP in BSD-flavor kernels.  UDP is a loss; udp_input calls
stripoptions() early on, and the code to save the srcrt is notdef'ed.
Linux is also still a loss at 1.3.x it looks like; the lsrr code is { }...
*/

/* if any -g arguments were given, set up source-routing.  We hit this after
   the gates are all looked up and ready to rock, any -G pointer is set,
   and gatesidx is now the *number* of hops */
  if (gatesidx) {		/* if we wanted any srcrt hops ... */
/* don't even bother compiling if we can't do IP options here! */
#ifdef IP_OPTIONS
    if (! optbuf) {		/* and don't already *have* a srcrt set */
      char * opp;		/* then do all this setup hair */
      optbuf = Hmalloc (48);
      opp = optbuf;
      *opp++ = IPOPT_LSRR;					/* option */
      *opp++ = (char)
	(((gatesidx + 1) * sizeof (IA)) + 3) & 0xff;		/* length */
      *opp++ = gatesptr;					/* pointer */
/* opp now points at first hop addr -- insert the intermediate gateways */
      for ( x = 0; x < gatesidx; x++) {
	memcpy (opp, gates[x]->iaddrs, sizeof (IA));
	opp += sizeof (IA);
      }
/* and tack the final destination on the end [needed!] */
      memcpy (opp, rad, sizeof (IA));
      opp += sizeof (IA);
      *opp = IPOPT_NOP;			/* alignment filler */
    } /* if empty optbuf */
/* calculate length of whole option mess, which is (3 + [hops] + [final] + 1),
   and apply it [have to do this every time through, of course] */
    x = ((gatesidx + 1) * sizeof (IA)) + 4;
    rr = setsockopt (nnetfd, IPPROTO_IP, IP_OPTIONS, optbuf, x);
    if (rr == -1)
      bail ("srcrt setsockopt fuxored");
#else /* IP_OPTIONS */
    holler ("Warning: source routing unavailable on this machine, ignoring");
#endif /* IP_OPTIONS*/
  } /* if gatesidx */

/* wrap connect inside a timer, and hit it */
  arm (1, o_wait);
  if (setjmp (jbuf) == 0) {
    rr = connect (nnetfd, (SA *)remend, sizeof (SA));
  } else {				/* setjmp: connect failed... */
    rr = -1;
    errno = ETIMEDOUT;			/* fake it */
  }
  arm (0, 0);
  if (rr == 0)
    return (nnetfd);
  close (nnetfd);			/* clean up junked socket FD!! */
  return (-1);
} /* doconnect */
