
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

#undef stdin
#undef stderr
#define sum(a, b) ((void (*)(FILE *,char *))funcs[0].addr)(a, b)
#define hex (*(int *)funcs[1].addr)
#define debug (*((int *)funcs[2].addr))
#define strcmp(a, b) ((int (*)(const char *,const char *))funcs[3].addr)(a, b)
#define fopen(a, b) ((FILE * (*)(const char *,const char *))funcs[4].addr)(a, b)
#define fclose(a) ((int (*)(FILE *))funcs[5].addr)(a)
#define fprintf(a, ...) ((int (*)(FILE *,const char *,...))funcs[6].addr)(a, __VA_ARGS__)
#define stdin (*(FILE **)funcs[7].addr)
#define stderr (*(FILE **)funcs[8].addr)

int
main(int argc, char **argv)
{
	int c;
	FILE *fd;
	argv++; argc--;
	if(argc>0 && strcmp(argv[0],"-d")==0){
		debug++;
		argv++; argc--;
	}

	if(argc>0 && strcmp(argv[0],"-x")==0){
		hex++;
		argv++; argc--;
	}

	if(argc == 0)
		sum(stdin,0);
	else for(c = 0; c < argc; c++){
		fd = fopen(argv[c],"r");
		if(fd==NULL){
			fprintf(stderr, "md5sum: can't open %s\n", argv[c]);
			continue;
		}
		sum(fd, argv[c]);
		fclose(fd);
	}
}
