
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define o_verbose (*(USHORT *)funcs[0].addr)
#define holler(...) ((void (*)(char *,...))funcs[1].addr)(__VA_ARGS__)
#define bail(...) ((void (*)(char *,...))funcs[2].addr)(__VA_ARGS__)

#ifdef HAVE_HELP		/* unless we wanna be *really* cryptic */
/* helpme :
   the obvious */
helpme()
{
  o_verbose = 1;
  holler ("[v1.10]\n\
connect to somewhere:	nc [-options] hostname port[s] [ports] ... \n\
listen for inbound:	nc -l -p port [-options] [hostname] [port]\n\
options:");
/* sigh, this necessarily gets messy.  And the trailing \ characters may be
   interpreted oddly by some compilers, generating or not generating extra
   newlines as they bloody please.  u-fix... */
#ifdef GAPING_SECURITY_HOLE	/* needs to be separate holler() */
  holler ("\
	-e prog			program to exec after connect [dangerous!!]");
#endif
  holler ("\
	-g gateway		source-routing hop point[s], up to 8\n\
	-G num			source-routing pointer: 4, 8, 12, ...\n\
	-h			this cruft\n\
	-i secs			delay interval for lines sent, ports scanned\n\
	-l			listen mode, for inbound connects\n\
	-n			numeric-only IP addresses, no DNS\n\
	-o file			hex dump of traffic\n\
	-p port			local port number\n\
	-r			randomize local and remote ports\n\
	-s addr			local source address");
#ifdef TELNET
  holler ("\
	-t			answer TELNET negotiation");
#endif
  holler ("\
	-u			UDP mode\n\
	-v			verbose [use twice to be more verbose]\n\
	-w secs			timeout for connects and final net reads\n\
	-z			zero-I/O mode [used for scanning]");
  bail ("port numbers can be individual or ranges: lo-hi [inclusive]");
} /* helpme */
#endif /* HAVE_HELP */

/* None genuine without this seal!  _H*/
