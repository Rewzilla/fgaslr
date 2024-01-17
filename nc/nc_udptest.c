
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_WRITE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BIGBUF_IN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_WAIT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_UDPMODE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DOCONNECT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define write(a,b,c) ((ssize_t (*)(int,const void *,size_t))funcs[0].addr)(a,b,c)
#define bigbuf_in (*(char **)funcs[1].addr)
#define holler(...) ((void (*)(char *,...))funcs[2].addr)(__VA_ARGS__)
#define errno (*(int *)funcs[3].addr)
#define o_wait (*(unsigned int *)funcs[4].addr)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[5].addr)(a)
#define o_udpmode (*(USHORT *)funcs[6].addr)
#define doconnect(a,b,c,d) ((int (*)(IA *,USHORT,IA *,USHORT))funcs[7].addr)(a,b,c,d)
#define close(a) ((int (*)(int))funcs[8].addr)(a)

/* udptest :
   fire a couple of packets at a UDP target port, just to see if it's really
   there.  On BSD kernels, ICMP host/port-unreachable errors get delivered to
   our socket as ECONNREFUSED write errors.  On SV kernels, we lose; we'll have
   to collect and analyze raw ICMP ourselves a la satan's probe_udp_ports
   backend.  Guess where one could swipe the appropriate code from...

   Use the time delay between writes if given, otherwise use the "tcp ping"
   trick for getting the RTT.  [I got that idea from pluvius, and warped it.]
   Return either the original fd, or clean up and return -1. */
udptest (fd, where)
  int fd;
  IA * where;
{
  register int rr;

  rr = write (fd, bigbuf_in, 1);
  if (rr != 1)
    holler ("udptest first write failed?! errno %d", errno);
  if (o_wait)
    sleep (o_wait);
  else {
/* use the tcp-ping trick: try connecting to a normally refused port, which
   causes us to block for the time that SYN gets there and RST gets back.
   Not completely reliable, but it *does* mostly work. */
    o_udpmode = 0;			/* so doconnect does TCP this time */
/* Set a temporary connect timeout, so packet filtration doesnt cause
   us to hang forever, and hit it */
    o_wait = 5;				/* enough that we'll notice?? */
    rr = doconnect (where, SLEAZE_PORT, 0, 0);
    if (rr > 0)
      close (rr);			/* in case it *did* open */
    o_wait = 0;				/* reset it */
    o_udpmode++;			/* we *are* still doing UDP, right? */
  } /* if o_wait */
  errno = 0;				/* clear from sleep */
  rr = write (fd, bigbuf_in, 1);
  if (rr == 1)				/* if write error, no UDP listener */
    return (fd);
  close (fd);				/* use it or lose it! */
  return (-1);
} /* udptest */
