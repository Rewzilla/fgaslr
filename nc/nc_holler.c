
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC___H_ERRNO_LOCATION), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_H_ERRS), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FPRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FFLUSH), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDERR), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC___ERRNO_LOCATION), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PERROR), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define o_verbose (*(USHORT *)funcs[0].addr)
#define __h_errno_location() ((int *(*)())funcs[1].addr)()
#define h_errs (*(static char **)funcs[2].addr)
#define fprintf(a, ...) ((int (*)(FILE *,const char *,...))funcs[3].addr)(a, __VA_ARGS__)
#define fflush(a) ((int (*)(FILE *))funcs[4].addr)(a)
#undef stderr
#define stderr (*(FILE **)funcs[5].addr)
#define __errno_location() ((int *(*)())funcs[6].addr)()
#define perror(a) ((void (*)(const char *))funcs[7].addr)(a)

/* holler :
   fake varargs -- need to do this way because we wind up calling through
   more levels of indirection than vanilla varargs can handle, and not all
   machines have vfprintf/vsyslog/whatever!  6 params oughta be enough. */
void holler (str, p1, p2, p3, p4, p5, p6)
  char * str;
  char * p1, * p2, * p3, * p4, * p5, * p6;
{
ASM_ALIGN_STACK();
  if (o_verbose) {
    fprintf (stderr, str, p1, p2, p3, p4, p5, p6);
#ifdef HAVE_BIND
    if (h_errno) {		/* if host-lookup variety of error ... */
      if (h_errno > 4)		/* oh no you don't, either */
	fprintf (stderr, "preposterous h_errno: %d", h_errno);
      else
	fprintf (stderr, h_errs[h_errno]);	/* handle it here */
      h_errno = 0;				/* and reset for next call */
    }
#endif
    if (errno) {		/* this gives funny-looking messages, but */
      perror (" ");		/* it's more portable than sys_errlist[]... */
    } else			/* xxx: do something better?  */
      fprintf (stderr, "\n");
    fflush (stderr);
  }
} /* holler */

