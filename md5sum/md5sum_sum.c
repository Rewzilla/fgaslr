
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_MD5), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_ENC64), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_HEX), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_NIL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CALLOC), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FREE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_PRINTF), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FREAD), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define md5(a, b, c, d) ((MD5state * (*)(byte *,uint,byte *,MD5state *))funcs[0].addr)(a, b, c, d)
#define enc64(a, b, c) ((int (*)(char *,uchar *,int))funcs[1].addr)(a, b, c)
#define hex (*(int *)funcs[2].addr)
#define nil (*(MD5state **)funcs[3].addr)
#define calloc(a, b) ((void * (*)(size_t,size_t))funcs[4].addr)(a, b)
#define free(a) ((void (*)(void *))funcs[5].addr)(a)
#define printf(...) ((int (*)(const char *,...))funcs[6].addr)(__VA_ARGS__)
#define fread(a, b, c, d) ((size_t (*)(void *,size_t,size_t,FILE *))funcs[7].addr)(a, b, c, d)

void
sum(FILE *fd, char *name)
{
	byte *buf;
	byte digest[16];
	char pr64[25];
	int i, n;
	MD5state *s;

	s = nil;
	n = 0;
	buf = calloc(256,64);
	for(;;){
		i = fread(buf+n, 1, 128*64-n, fd);
		if(i <= 0)
			break;
		n += i;
		if(n & 0x3f)
			continue;
		s = md5(buf, n, 0, s);
		n = 0;
	}
	md5(buf, n, digest, s);
	if(hex){
		for(i=0;i<16;i++) printf("%.2X", digest[i]);
	}else{
		enc64(pr64,digest,sizeof(digest));
		pr64[22] = '\0';  /* chop trailing == */
		printf("%s",pr64);
	}
	if(name)
		printf("\t%s", name);
	printf("\n");
	free(buf);
}
