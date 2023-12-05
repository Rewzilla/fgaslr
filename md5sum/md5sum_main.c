
#include "md5sum_types.h"
#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_SUM), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HEX), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DEBUG), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STRCMP), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FOPEN), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FCLOSE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FPRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDIN), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_STDERR), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define FGASLR_SUM(a, b) ((void (*)(FILE *,char *))funcs[0].addr)(a, b)
#define FGASLR_HEX (*(int *)funcs[1].addr)
#define FGASLR_DEBUG (*((int *)funcs[2].addr))
#define FGASLR_STRCMP(a, b) ((int (*)(const char *,const char *))funcs[3].addr)(a, b)
#define FGASLR_FOPEN(a, b) ((FILE * (*)(const char *,const char *))funcs[4].addr)(a, b)
#define FGASLR_FCLOSE(a) ((int (*)(FILE *))funcs[5].addr)(a)
#define FGASLR_FPRINTF(a, ...) ((int (*)(FILE *,const char *,...))funcs[6].addr)(a, __VA_ARGS__)
#define FGASLR_STDIN (*(FILE **)funcs[7].addr)
#define FGASLR_STDERR (*(FILE **)funcs[8].addr)

int
main(int argc, char **argv)
{
	int c;
	FILE *fd;
	argv++; argc--;
	if(argc>0 && FGASLR_STRCMP(argv[0],"-d")==0){
		FGASLR_DEBUG++;
		argv++; argc--;
	}

	if(argc>0 && FGASLR_STRCMP(argv[0],"-x")==0){
		FGASLR_HEX++;
		argv++; argc--;
	}

	if(argc == 0)
		FGASLR_SUM(FGASLR_STDIN,0);
	else for(c = 0; c < argc; c++){
		fd = FGASLR_FOPEN(argv[c],"r");
		if(fd==NULL){
			FGASLR_FPRINTF(FGASLR_STDERR, "md5sum: can't open %s\n", argv[c]);
			continue;
		}
		FGASLR_SUM(fd, argv[c]);
		FGASLR_FCLOSE(fd);
	}
}
