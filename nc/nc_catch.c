
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_LIBC, FUNC_ERRNO), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_BAIL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_TXT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_NET), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_WROTE_OUT), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define errno (*(int *)funcs[0].addr)
#define o_verbose (*(USHORT *)funcs[1].addr)
#define bail(a,b,c,d,e,f,g) ((void (*)(char *,char *,char *,char *,char *,char *,char *,))funcs[2].addr)(a,b,c,d,e,f,g) 
#define wrote_txt ((static char *)funcs[3].addr)
#define wrote_net (*(int *)funcs[4].addr)
#define wrote_out (*(int *)funcs[5].addr)

/* catch :
   no-brainer interrupt handler */
void catch ()
{
  errno = 0;
  if (o_verbose > 1)		/* normally we don't care */
    bail (wrote_txt, wrote_net, wrote_out);
  bail (" punt!");
}
