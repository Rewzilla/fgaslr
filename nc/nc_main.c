
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_RES_INIT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_LCLEND), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_REMEND), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HMALLOC), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BIGBUF_IN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BIGBUF_NET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DING1), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DING2), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_PORTPOOP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GATESPTR), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_H_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SIGNAL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FPRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FFLUSH), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_READ), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_FINDLINE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMCPY), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCHR), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_GETOPT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_ALLA), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_PR00GIE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ATOI), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GATESIDX), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GATES), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GETHOSTPOOP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_NFLAG), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HELPME), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_INTERVAL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_LISTEN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_STAGE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_WFILE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_GETPORTPOOP), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_RANDOM), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_TN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_UDPMODE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_WAIT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_TIMER1), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_TIMER2), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_ZERO), NULL},
	// These are necessary for the Debug() macro
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDOUT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_TIME), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_OFD), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_OPEN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_NETFD), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DOLISTEN), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DOEXEC), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_READWRITE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_NET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_OUT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_TXT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_SINGLE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_LOADPORTS), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_NEXTPORT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DOCONNECT), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_EXIT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_INSAVED), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_CATCH), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_CATCH), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define res_init() ((int (*)())funcs[0].addr)()
#define lclend (*(SAI **)funcs[1].addr)
#define remend (*(SAI **)funcs[2].addr)
#define Hmalloc(a) ((char * (*)(unsigned int))funcs[3].addr)(a)
#define bigbuf_in (*(char **)funcs[4].addr)
#define bigbuf_net (*(char **)funcs[5].addr)
#define ding1 (*(fd_set **)funcs[6].addr)
#define ding2 (*(fd_set **)funcs[7].addr)
#define portpoop (*(PINF **)funcs[8].addr)
#define errno (*(int *)funcs[9].addr)
#define gatesptr (*(int *)funcs[10].addr)
#define h_errno (*(int *)funcs[11].addr)
#define signal(a,b) ((sighandler_t (*)(int,sighandler_t))funcs[12].addr)(a,b)
#define fprintf(a, ...) ((int (*)(FILE *,const char *,...))funcs[13].addr)(a, __VA_ARGS__)
#define fflush(a) ((int (*)(FILE *))funcs[14].addr)(a)
#define read(a,b,c) ((ssize_t (*)(int,const void *,size_t))funcs[15].addr)(a,b,c)
#define bail(...) ((void (*)(char *,...))funcs[16].addr)(__VA_ARGS__)
#define findline(a,b) ((unsigned int (*)(char *,unsigned int))funcs[17].addr)(a,b)
#define memcpy(a,b,c) ((void * (*)(void *,const void *,size_t))funcs[18].addr)(a,b,c)
#define strchr(a,b) ((char * (*)(const char *,int))funcs[19].addr)(a,b)
#define getopt(a,b,c) ((int (*)(int,char **,const char *))funcs[20].addr)(a,b,c)
#define o_alla (*(USHORT *)funcs[21].addr)
#define pr00gie (*(char **)funcs[22].addr)
#define atoi(a) ((int (*)(const char *))funcs[23].addr)(a)
#define gatesidx (*(int *)funcs[24].addr)
#define gates (*(HINF ***)funcs[25].addr)
#define gethostpoop(a,b) ((HINF * (*)(char *,USHORT))funcs[26].addr)(a,b)
#define o_nflag (*(USHORT *)funcs[27].addr)
#define helpme() ((void (*)())funcs[28].addr)()
#define o_interval (*(unsigned int *)funcs[29].addr)
#define o_listen (*(USHORT *)funcs[30].addr)
#define stage (*(unsigned char **)funcs[31].addr)
#define o_wfile (*(USHORT *)funcs[32].addr)
#define getportpoop(a,b) ((USHORT (*)(char *,unsigned int))funcs[33].addr)(a,b)
#define o_random (*(USHORT *)funcs[34].addr)
#define o_tn (*(USHORT *)funcs[35].addr)
#define o_udpmode (*(USHORT *)funcs[36].addr)
#define o_verbose (*(USHORT *)funcs[37].addr)
#define o_wait (*(unsigned int *)funcs[38].addr)
#define timer1 (*(struct timeval **)funcs[39].addr)
#define timer2 (*(struct timeval **)funcs[40].addr)
#define o_zero (*(USHORT *)funcs[41].addr)
#define printf(...) ((int (*)(const char *,...))funcs[42].addr)(a, __VA_ARGS__)
#undef stdout
#define stdout (*(FILE **)funcs[43].addr)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[44].addr)(a)
#define time(a) ((time_t (*)(time_t *))funcs[45].addr)(a)
#define close(a) ((int (*)(int))funcs[46].addr)(a)
#define ofd (*(int *)funcs[47].addr)
#define open(a,b,...) ((int (*)(unsigned char *,int,...))funcs[48].addr)(a,b,__VA_ARGS__)
#define netfd (*(int *)funcs[49].addr)
#define dolisten(a,b,c,d) ((int (*)(IA *,USHORT,IA *,USHORT))funcs[50].addr)(a,b,c,d)
#define doexec(a) ((void (*)(int))funcs[51].addr)(a)
#define readwrite(a) ((int (*)(int))funcs[52].addr)(a)
#define holler(...) ((void (*)(char *,...))funcs[53].addr)(__VA_ARGS__)
#define wrote_net (*(int *)funcs[54].addr)
#define wrote_out (*(int *)funcs[55].addr)
#define wrote_txt ((char *)funcs[56].addr)
#define Single (*(USHORT *)funcs[57].addr)
#define loadports(a,b,c) ((void (*)(char *,USHORT,USHORT))funcs[58].addr)(a,b,c)
#define nextport(a) ((USHORT (*)(char *))funcs[59].addr)(a)
#define doconnect(a,b,c,d) ((int (*)(IA *,USHORT,IA *,USHORT))funcs[60].addr)(a,b,c,d)
#define exit(a) ((void (*)(int))funcs[60].addr)(a)
#define insaved (*(unsigned int *)funcs[62].addr)
#define catch ((void (*)())funcs[63].addr)
#define udptest(a,b) ((int (*)(int,IA *))funcs[64].addr)(a,b)

/* main :
   now we pull it all together... */
main (argc, argv)
  int argc;
  char ** argv;
{
#ifndef HAVE_GETOPT
  extern char * optarg;
  extern int optind, optopt;
#endif
  register int x;
  register char *cp;
  HINF * gp;
  HINF * whereto = NULL;
  HINF * wherefrom = NULL;
  IA * ouraddr = NULL;
  IA * themaddr = NULL;
  USHORT o_lport = 0;
  USHORT ourport = 0;
  USHORT loport = 0;		/* for scanning stuff */
  USHORT hiport = 0;
  USHORT curport = 0;
  char * randports = NULL;

#ifdef HAVE_BIND
/* can *you* say "cc -yaddayadda netcat.c -lresolv -l44bsd" on SunLOSs? */
  res_init();
#endif
/* I was in this barbershop quartet in Skokie IL ... */
/* round up the usual suspects, i.e. malloc up all the stuff we need */
  lclend = (SAI *) Hmalloc (sizeof (SA));
  remend = (SAI *) Hmalloc (sizeof (SA));
  bigbuf_in = Hmalloc (BIGSIZ);
  bigbuf_net = Hmalloc (BIGSIZ);
  ding1 = (fd_set *) Hmalloc (sizeof (fd_set));
  ding2 = (fd_set *) Hmalloc (sizeof (fd_set));
  portpoop = (PINF *) Hmalloc (sizeof (PINF));

  errno = 0;
  gatesptr = 4;
  h_errno = 0;

/* catch a signal or two for cleanup */
  signal (SIGINT, catch);
  signal (SIGQUIT, catch);
  signal (SIGTERM, catch);
/* and suppress others... */
#ifdef SIGURG
  signal (SIGURG, SIG_IGN);
#endif
#ifdef SIGPIPE
  signal (SIGPIPE, SIG_IGN);		/* important! */
#endif

/* if no args given at all, get 'em from stdin, construct an argv, and hand
   anything left over to readwrite(). */
  if (argc == 1) {
    cp = argv[0];
    argv = (char **) Hmalloc (128 * sizeof (char *));	/* XXX: 128? */
    argv[0] = cp;			/* leave old prog name intact */
    cp = Hmalloc (BIGSIZ);
    argv[1] = cp;			/* head of new arg block */
    fprintf (stderr, "Cmd line: ");
    fflush (stderr);		/* I dont care if it's unbuffered or not! */
    insaved = read (0, cp, BIGSIZ);	/* we're gonna fake fgets() here */
    if (insaved <= 0)
      bail ("wrong");
    x = findline (cp, insaved);
    if (x)
      insaved -= x;		/* remaining chunk size to be sent */
    if (insaved)		/* which might be zero... */
      memcpy (bigbuf_in, &cp[x], insaved);
    cp = strchr (argv[1], '\n');
    if (cp)
      *cp = '\0';
    cp = strchr (argv[1], '\r');	/* look for ^M too */
    if (cp)
      *cp = '\0';

/* find and stash pointers to remaining new "args" */
    cp = argv[1];
    cp++;				/* skip past first char */
    x = 2;				/* we know argv 0 and 1 already */
    for (; *cp != '\0'; cp++) {
      if (*cp == ' ') {
	*cp = '\0';			/* smash all spaces */
	continue;
      } else {
	if (*(cp-1) == '\0') {
	  argv[x] = cp;
	  x++;
	}
      } /* if space */
    } /* for cp */
    argc = x;
  } /* if no args given */

/* If your shitbox doesn't have getopt, step into the nineties already. */
/* optarg, optind = next-argv-component [i.e. flag arg]; optopt = last-char */
  while ((x = getopt (argc, argv, "ae:g:G:hi:lno:p:rs:tuvw:z")) != EOF) {
/* Debug (("in go: x now %c, optarg %x optind %d", x, optarg, optind)) */
    switch (x) {
      case 'a':
	bail ("all-A-records NIY");
	o_alla++; break;
#ifdef GAPING_SECURITY_HOLE
      case 'e':				/* prog to exec */
	pr00gie = optarg;
	break;
#endif
      case 'G':				/* srcrt gateways pointer val */
	x = atoi (optarg);
	if ((x) && (x == (x & 0x1c)))	/* mask off bits of fukt values */
	  gatesptr = x;
	else
	  bail ("invalid hop pointer %d, must be multiple of 4 <= 28", x);
	break;
      case 'g':				/* srcroute hop[s] */
	if (gatesidx > 8)
	  bail ("too many -g hops");
	if (gates == NULL)		/* eat this, Billy-boy */
	  gates = (HINF **) Hmalloc (sizeof (HINF *) * 10);
	gp = gethostpoop (optarg, o_nflag);
	if (gp)
	  gates[gatesidx] = gp;
	gatesidx++;
	break;
      case 'h':
	errno = 0;
#ifdef HAVE_HELP
	helpme();			/* exits by itself */
#else
	bail ("no help available, dork -- RTFS");
#endif
      case 'i':				/* line-interval time */
	o_interval = atoi (optarg) & 0xffff;
	if (! o_interval)
	  bail ("invalid interval time %s", optarg);
	break;
      case 'l':				/* listen mode */
	o_listen++; break;
      case 'n':				/* numeric-only, no DNS lookups */
	o_nflag++; break;
      case 'o':				/* hexdump log */
	stage = (unsigned char *) optarg;
	o_wfile++; break;
      case 'p':				/* local source port */
	o_lport = getportpoop (optarg, 0);
	if (o_lport == 0)
	  bail ("invalid local port %s", optarg);
	break;
      case 'r':				/* randomize various things */
	o_random++; break;
      case 's':				/* local source address */
/* do a full lookup [since everything else goes through the same mill],
   unless -n was previously specified.  In fact, careful placement of -n can
   be useful, so we'll still pass o_nflag here instead of forcing numeric.  */
	wherefrom = gethostpoop (optarg, o_nflag);
	ouraddr = &wherefrom->iaddrs[0];
	break;
#ifdef TELNET
      case 't':				/* do telnet fakeout */
	o_tn++; break;
#endif /* TELNET */
      case 'u':				/* use UDP */
	o_udpmode++; break;
      case 'v':				/* verbose */
	o_verbose++; break;
      case 'w':				/* wait time */
	o_wait = atoi (optarg);
	if (o_wait <= 0)
	  bail ("invalid wait-time %s", optarg);
	timer1 = (struct timeval *) Hmalloc (sizeof (struct timeval));
	timer2 = (struct timeval *) Hmalloc (sizeof (struct timeval));
	timer1->tv_sec = o_wait;	/* we need two.  see readwrite()... */
	break;
      case 'z':				/* little or no data xfer */
	o_zero++;
	break;
      default:
	errno = 0;
	bail ("nc -h for help");
    } /* switch x */
  } /* while getopt */

/* other misc initialization */
Debug (("fd_set size %d", sizeof (*ding1)))	/* how big *is* it? */
  FD_SET (0, ding1);			/* stdin *is* initially open */
  if (o_random) {
    SRAND (time (0));
    randports = Hmalloc (65536);	/* big flag array for ports */
  }
#ifdef GAPING_SECURITY_HOLE
  if (pr00gie) {
    close (0);				/* won't need stdin */
    o_wfile = 0;			/* -o with -e is meaningless! */
    ofd = 0;
  }
#endif /* G_S_H */
  if (o_wfile) {
    ofd = open (stage, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (ofd <= 0)			/* must be > extant 0/1/2 */
      bail ("can't open %s", stage);
    stage = (unsigned char *) Hmalloc (100);
  }

/* optind is now index of first non -x arg */
Debug (("after go: x now %c, optarg %x optind %d", x, optarg, optind))
/* Debug (("optind up to %d at host-arg %s", optind, argv[optind])) */
/* gonna only use first addr of host-list, like our IQ was normal; if you wanna
   get fancy with addresses, look up the list yourself and plug 'em in for now.
   unless we finally implement -a, that is. */
  if (argv[optind])
    whereto = gethostpoop (argv[optind], o_nflag);
  if (whereto && whereto->iaddrs)
    themaddr = &whereto->iaddrs[0];
  if (themaddr)
    optind++;				/* skip past valid host lookup */
  errno = 0;
  h_errno = 0;

/* Handle listen mode here, and exit afterward.  Only does one connect;
   this is arguably the right thing to do.  A "persistent listen-and-fork"
   mode a la inetd has been thought about, but not implemented.  A tiny
   wrapper script can handle such things... */
  if (o_listen) {
    curport = 0;			/* rem port *can* be zero here... */
    if (argv[optind]) {			/* any rem-port-arg? */
      curport = getportpoop (argv[optind], 0);
      if (curport == 0)			/* if given, demand correctness */
	bail ("invalid port %s", argv[optind]);
    } /* if port-arg */
    netfd = dolisten (themaddr, curport, ouraddr, o_lport);
/* dolisten does its own connect reporting, so we don't holler anything here */
    if (netfd > 0) {
#ifdef GAPING_SECURITY_HOLE
      if (pr00gie)			/* -e given? */
	doexec (netfd);
#endif /* GAPING_SECURITY_HOLE */
      x = readwrite (netfd);		/* it even works with UDP! */
      if (o_verbose > 1)		/* normally we don't care */
	holler (wrote_txt, wrote_net, wrote_out);
      exit (x);				/* "pack out yer trash" */
    } else /* if no netfd */
      bail ("no connection");
  } /* o_listen */

/* fall thru to outbound connects.  Now we're more picky about args... */
  if (! themaddr)
    bail ("no destination");
  if (argv[optind] == NULL)
    bail ("no port[s] to connect to");
  if (argv[optind + 1])		/* look ahead: any more port args given? */
    Single = 0;				/* multi-mode, case A */
  ourport = o_lport;			/* which can be 0 */

/* everything from here down is treated as as ports and/or ranges thereof, so
   it's all enclosed in this big ol' argv-parsin' loop.  Any randomization is
   done within each given *range*, but in separate chunks per each succeeding
   argument, so we can control the pattern somewhat. */
  while (argv[optind]) {
    hiport = loport = 0;
    cp = strchr (argv[optind], '-');	/* nn-mm range? */
    if (cp) {
      *cp = '\0';
      cp++;
      hiport = getportpoop (cp, 0);
      if (hiport == 0)
	bail ("invalid port %s", cp);
    } /* if found a dash */
    loport = getportpoop (argv[optind], 0);
    if (loport == 0)
      bail ("invalid port %s", argv[optind]);
    if (hiport > loport) {		/* was it genuinely a range? */
      Single = 0;			/* multi-mode, case B */
      curport = hiport;			/* start high by default */
      if (o_random) {			/* maybe populate the random array */
	loadports (randports, loport, hiport);
	curport = nextport (randports);
      }
    } else			/* not a range, including args like "25-25" */
      curport = loport;
Debug (("Single %d, curport %d", Single, curport))

/* Now start connecting to these things.  curport is already preloaded. */
    while (loport <= curport) {
      if ((! o_lport) && (o_random)) {	/* -p overrides random local-port */
	ourport = (RAND() & 0xffff);	/* random local-bind -- well above */
	if (ourport < 8192)		/* resv and any likely listeners??? */
	  ourport += 8192;		/* if it *still* conflicts, use -s. */
      }
      curport = getportpoop (NULL, curport);
      netfd = doconnect (themaddr, curport, ouraddr, ourport);
Debug (("netfd %d from port %d to port %d", netfd, ourport, curport))
      if (netfd > 0)
	if (o_zero && o_udpmode)	/* if UDP scanning... */
	  netfd = udptest (netfd, themaddr);
      if (netfd > 0) {			/* Yow, are we OPEN YET?! */
	x = 0;				/* pre-exit status */
	holler ("%s [%s] %d (%s) open",
	  whereto->name, whereto->addrs[0], curport, portpoop->name);
#ifdef GAPING_SECURITY_HOLE
	if (pr00gie)			/* exec is valid for outbound, too */
	  doexec (netfd);
#endif /* GAPING_SECURITY_HOLE */
	if (! o_zero)
	  x = readwrite (netfd);	/* go shovel shit */
      } else { /* no netfd... */
	x = 1;				/* preload exit status for later */
/* if we're scanning at a "one -v" verbosity level, don't print refusals.
   Give it another -v if you want to see everything. */
	if ((Single || (o_verbose > 1)) || (errno != ECONNREFUSED))
	  holler ("%s [%s] %d (%s)",
	    whereto->name, whereto->addrs[0], curport, portpoop->name);
      } /* if netfd */
      close (netfd);			/* just in case we didn't already */
      if (o_interval)
	sleep (o_interval);		/* if -i, delay between ports too */
      if (o_random)
	curport = nextport (randports);
      else
	curport--;			/* just decrement... */
    } /* while curport within current range */
    optind++;
  } /* while remaining port-args -- end of big argv-ports loop*/

  errno = 0;
  if (o_verbose > 1)		/* normally we don't care */
    holler (wrote_txt, wrote_net, wrote_out);
  if (Single)
    exit (x);			/* give us status on one connection */
  exit (0);			/* otherwise, we're just done */
} /* main */
