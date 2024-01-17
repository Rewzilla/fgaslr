
#include "nc.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_O_VERBOSE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HOLLER), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CLOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_SLEEP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_EXIT), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_NETFD), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define o_verbose (*(USHORT *)funcs[0].addr)
#define holler(...) ((void (*)(char *,...))funcs[1].addr)(__VA_ARGS__)
#define close(a) ((int (*)(int))funcs[2].addr)(a)
#define sleep(a) ((unsigned int (*)(unsigned int))funcs[3].addr)(a)
#define exit(a) ((void (*)(int))funcs[4].addr)(a)
#define netfd (*(int *)funcs[5].addr)

/* bail :
   error-exit handler, callable from anywhere */
void bail (str, p1, p2, p3, p4, p5, p6)
  char * str;
  char * p1, * p2, * p3, * p4, * p5, * p6;
{
  o_verbose = 1;
  holler (str, p1, p2, p3, p4, p5, p6);
  close (netfd);
  sleep (1);
  exit (1);
} /* bail */
