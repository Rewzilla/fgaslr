
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#ifdef HAVE_BIND
/* stolen almost wholesale from bsd herror.c */
static char * h_errs[] = {
  "Error 0",				/* but we *don't* use this */
  "Unknown host",			/* 1 HOST_NOT_FOUND */
  "Host name lookup failure",		/* 2 TRY_AGAIN */
  "Unknown server error",		/* 3 NO_RECOVERY */
  "No address associated with name",	/* 4 NO_ADDRESS */
};
#endif /* HAVE_BIND */
