
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MALLOC), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMSET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define malloc(a) ((void * (*)(size_t))funcs[0].addr)(a)
#define memset(a,b,c) ((void * (*)(void *,int,size_t))funcs[1].addr)(a,b,c)
#define bail(...) ((void (*)(char *,...))funcs[2].addr)(__VA_ARGS__)

/* Hmalloc :
   malloc up what I want, rounded up to *4, and pre-zeroed.  Either succeeds
   or bails out on its own, so that callers don't have to worry about it. */
char * Hmalloc (size)
  unsigned int size;
{
  unsigned int s = (size + 4) & 0xfffffffc;	/* 4GB?! */
  char * p = malloc (s);
  if (p != NULL)
    memset (p, 0, s);
  else
    bail ("Hmalloc %d failed", s);
  return (p);
} /* Hmalloc */
