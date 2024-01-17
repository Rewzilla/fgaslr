
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DING1), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BIGBUF_IN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_SINGLE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_INTERVAL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DING2), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_TIMER1), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMCPY), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_TIMER2), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SELECT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_READ), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BIGBUF_NET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_TN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_ATELNET), NULL},
	// These are necessary for the Debug() macro
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FFLUSH), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDOUT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_WRITE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_WFILE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_OPRINT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_OUT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_FINDLINE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_NET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_INSAVED), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define holler(...) ((void (*)(char *,...))funcs[0].addr)(__VA_ARGS__)
#define ding1 (*(fd_set **)funcs[1].addr)
#define bigbuf_in (*(char **)funcs[2].addr)
#define Single (*(USHORT *)funcs[3].addr)
#define close(a) ((int (*)(int))funcs[4].addr)(a)
#define o_interval (*(unsigned int *)funcs[5].addr)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[6].addr)(a)
#define errno (*(int *)funcs[7].addr)
#define ding2 (*(fd_set **)funcs[8].addr)
#define timer1 (*(struct timeval **)funcs[9].addr)
#define memcpy(a,b,c) ((void * (*)(void *,const void *,size_t))funcs[10].addr)(a,b,c)
#define timer2 (*(struct timeval **)funcs[11].addr)
#define select(a,b,c,d,e) ((int (*)(int,fd_set *,fd_set *,fd_set *,struct timeval *))funcs[12].addr)(a,b,c,d,e)
#define o_verbose (*(USHORT *)funcs[13].addr)
#define read(a,b,c) ((ssize_t (*)(int,const void *,size_t))funcs[14].addr)(a,b,c)
#define bigbuf_net (*(char **)funcs[15].addr)
#define o_tn (*(USHORT *)funcs[16].addr)
#define atelnet(a,b) ((void (*)(unsigned char *,unsigned int))funcs[17].addr)(a,b)
#define printf(...) ((int (*)(const char *,...))funcs[18].addr)(a, __VA_ARGS__)
#define fflush(a) ((int (*)(FILE *))funcs[19].addr)(a)
#define stdout (*(FILE **)funcs[20].addr)
#define write(a,b,c) ((ssize_t (*)(int,const void *,size_t))funcs[21].addr)(a,b,c)
#define o_wfile (*(USHORT *)funcs[22].addr)
#define oprint(a,b,c) ((void (*)(int,char *,int))funcs[23].addr)(a,b,c)
#define wrote_out (*(int *)funcs[24].addr)
#define findline(a,b) ((unsigned int (*)(char *,unsigned int))funcs[25].addr)(a,b)
#define wrote_net (*(int *)funcs[26].addr)
#define insaved (*(unsigned int *)funcs[27].addr)

/* readwrite :
   handle stdin/stdout/network I/O.  Bwahaha!! -- the select loop from hell.
   In this instance, return what might become our exit status. */
int readwrite (fd)
  int fd;
{
  register int rr;
  register char * zp;		/* stdin buf ptr */
  register char * np;		/* net-in buf ptr */
  unsigned int rzleft;
  unsigned int rnleft;
  USHORT netretry;		/* net-read retry counter */
  USHORT wretry;		/* net-write sanity counter */
  USHORT wfirst;		/* one-shot flag to skip first net read */

/* if you don't have all this FD_* macro hair in sys/types.h, you'll have to
   either find it or do your own bit-bashing: *ding1 |= (1 << fd), etc... */
  if (fd > FD_SETSIZE) {
    holler ("Preposterous fd value %d", fd);
    return (1);
  }
  FD_SET (fd, ding1);		/* global: the net is open */
  netretry = 2;
  wfirst = 0;
  rzleft = rnleft = 0;
  if (insaved) {
    rzleft = insaved;		/* preload multi-mode fakeouts */
    zp = bigbuf_in;
    wfirst = 1;
    if (Single)			/* if not scanning, this is a one-off first */
      insaved = 0;		/* buffer left over from argv construction, */
    else {
      FD_CLR (0, ding1);	/* OR we've already got our repeat chunk, */
      close (0);		/* so we won't need any more stdin */
    } /* Single */
  } /* insaved */
  if (o_interval)
    sleep (o_interval);		/* pause *before* sending stuff, too */
  errno = 0;			/* clear from sleep, close, whatever */

/* and now the big ol' select shoveling loop ... */
  while (FD_ISSET (fd, ding1)) {	/* i.e. till the *net* closes! */
    wretry = 8200;			/* more than we'll ever hafta write */
    if (wfirst) {			/* any saved stdin buffer? */
      wfirst = 0;			/* clear flag for the duration */
      goto shovel;			/* and go handle it first */
    }
    *ding2 = *ding1;			/* FD_COPY ain't portable... */
/* some systems, notably linux, crap into their select timers on return, so
   we create a expendable copy and give *that* to select.  *Fuck* me ... */
    if (timer1)
      memcpy (timer2, timer1, sizeof (struct timeval));
    rr = select (16, ding2, 0, 0, timer2);	/* here it is, kiddies */
    if (rr < 0) {
	if (errno != EINTR) {		/* might have gotten ^Zed, etc ?*/
	  holler ("select fuxored");
	  close (fd);
	  return (1);
	}
    } /* select fuckup */
/* if we have a timeout AND stdin is closed AND we haven't heard anything
   from the net during that time, assume it's dead and close it too. */
    if (rr == 0) {
	if (! FD_ISSET (0, ding1))
	  netretry--;			/* we actually try a coupla times. */
	if (! netretry) {
	  if (o_verbose > 1)		/* normally we don't care */
	    holler ("net timeout");
	  close (fd);
	  return (0);			/* not an error! */
	}
    } /* select timeout */
/* xxx: should we check the exception fds too?  The read fds seem to give
   us the right info, and none of the examples I found bothered. */

/* Ding!!  Something arrived, go check all the incoming hoppers, net first */
    if (FD_ISSET (fd, ding2)) {		/* net: ding! */
	rr = read (fd, bigbuf_net, BIGSIZ);
	if (rr <= 0) {
	  FD_CLR (fd, ding1);		/* net closed, we'll finish up... */
	  rzleft = 0;			/* can't write anymore: broken pipe */
	} else {
	  rnleft = rr;
	  np = bigbuf_net;
#ifdef TELNET
	  if (o_tn)
	    atelnet (np, rr);		/* fake out telnet stuff */
#endif /* TELNET */
	} /* if rr */
Debug (("got %d from the net, errno %d", rr, errno))
    } /* net:ding */

/* if we're in "slowly" mode there's probably still stuff in the stdin
   buffer, so don't read unless we really need MORE INPUT!  MORE INPUT! */
    if (rzleft)
	goto shovel;

/* okay, suck more stdin */
    if (FD_ISSET (0, ding2)) {		/* stdin: ding! */
	rr = read (0, bigbuf_in, BIGSIZ);
/* Considered making reads here smaller for UDP mode, but 8192-byte
   mobygrams are kinda fun and exercise the reassembler. */
	if (rr <= 0) {			/* at end, or fukt, or ... */
	  FD_CLR (0, ding1);		/* disable and close stdin */
	  close (0);
	} else {
	  rzleft = rr;
	  zp = bigbuf_in;
/* special case for multi-mode -- we'll want to send this one buffer to every
   open TCP port or every UDP attempt, so save its size and clean up stdin */
	  if (! Single) {		/* we might be scanning... */
	    insaved = rr;		/* save len */
	    FD_CLR (0, ding1);		/* disable further junk from stdin */
	    close (0);			/* really, I mean it */
	  } /* Single */
	} /* if rr/read */
    } /* stdin:ding */

shovel:
/* now that we've dingdonged all our thingdings, send off the results.
   Geez, why does this look an awful lot like the big loop in "rsh"? ...
   not sure if the order of this matters, but write net -> stdout first. */

/* sanity check.  Works because they're both unsigned... */
    if ((rzleft > 8200) || (rnleft > 8200)) {
	holler ("Bogus buffers: %d, %d", rzleft, rnleft);
	rzleft = rnleft = 0;
    }
/* net write retries sometimes happen on UDP connections */
    if (! wretry) {			/* is something hung? */
	holler ("too many output retries");
	return (1);
    }
    if (rnleft) {
	rr = write (1, np, rnleft);
	if (rr > 0) {
	  if (o_wfile)
	    oprint (1, np, rr);		/* log the stdout */
	  np += rr;			/* fix up ptrs and whatnot */
	  rnleft -= rr;			/* will get sanity-checked above */
	  wrote_out += rr;		/* global count */
	}
Debug (("wrote %d to stdout, errno %d", rr, errno))
    } /* rnleft */
    if (rzleft) {
	if (o_interval)			/* in "slowly" mode ?? */
	  rr = findline (zp, rzleft);
	else
	  rr = rzleft;
	rr = write (fd, zp, rr);	/* one line, or the whole buffer */
	if (rr > 0) {
	  if (o_wfile)
	    oprint (0, zp, rr);		/* log what got sent */
	  zp += rr;
	  rzleft -= rr;
	  wrote_net += rr;		/* global count */
	}
Debug (("wrote %d to net, errno %d", rr, errno))
    } /* rzleft */
    if (o_interval) {			/* cycle between slow lines, or ... */
	sleep (o_interval);
	errno = 0;			/* clear from sleep */
	continue;			/* ...with hairy select loop... */
    }
    if ((rzleft) || (rnleft)) {		/* shovel that shit till they ain't */
	wretry--;			/* none left, and get another load */
	goto shovel;
    }
  } /* while ding1:netfd is open */

/* XXX: maybe want a more graceful shutdown() here, or screw around with
   linger times??  I suspect that I don't need to since I'm always doing
   blocking reads and writes and my own manual "last ditch" efforts to read
   the net again after a timeout.  I haven't seen any screwups yet, but it's
   not like my test network is particularly busy... */
  close (fd);
  return (0);
} /* readwrite */
