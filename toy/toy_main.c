#include <stdio.h>

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_ADD), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_MUL), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DIV), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PRINTF), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define FGASLR_ADD(a, b) ((int (*)(int, int))funcs[0].addr)(a, b)
#define FGASLR_MUL(a, b) ((int (*)(int, int))funcs[1].addr)(a, b)
#define FGASLR_DIV(a, b) ((double (*)(double, double))funcs[2].addr)(a, b)
#define FGASLR_PRINTF(a, ...) (((void (*)())funcs[3].addr))(a, __VA_ARGS__)

int main(int argc, char *argv[]) {

	int r1, r2, r3;
	double r4, r5;

	FGASLR_PRINTF("argc = %d, argv[1] = %s\n", argc, argv[1]);

	// r1 = add(10, 7);
	r1 = FGASLR_ADD(10, 7);

	// r2 = add(9, 4);
	r2 = FGASLR_ADD(9, 4);

	// r3 = mul(r1, r2);
	r3 = FGASLR_MUL(r1, r2);

//	ASM_BREAKPOINT();

	// printf("r3 result = %d\n", r3);
	FGASLR_PRINTF("r3 result = %d\n", r3);

	// r4 = div(10.0, 3.0);
	r4 = FGASLR_DIV(10.0, 3.0);

	// printf("r4 result = %lf\n", r4);
	FGASLR_PRINTF("r4 result = %lf\n", r4);

	// r5 = div(2.2, 3.3);
	r5 = FGASLR_DIV(2.2, 2.0);

	// printf("r5 result = %lf\n", r5);
	FGASLR_PRINTF("r5 result = %lf\n", r5);

}