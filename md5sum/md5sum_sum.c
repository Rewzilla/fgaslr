
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

#define FGASLR_MD5(a, b, c, d) ((MD5state * (*)(byte *,uint,byte *,MD5state *))funcs[0].addr)(a, b, c, d)
#define FGASLR_ENC64(a, b, c) ((int (*)(char *,uchar *,int))funcs[1].addr)(a, b, c)
#define FGASLR_HEX (*(int *)funcs[2].addr)
#define FGASLR_NIL (*(MD5state **)funcs[3].addr)
#define FGASLR_CALLOC(a, b) ((void * (*)(size_t,size_t))funcs[4].addr)(a, b)
#define FGASLR_FREE(a) ((void (*)(void *))funcs[5].addr)(a)
#define FGASLR_PRINTF(...) ((int (*)(const char *,...))funcs[6].addr)(__VA_ARGS__)
#define FGASLR_FREAD(a, b, c, d) ((size_t (*)(void *,size_t,size_t,FILE *))funcs[7].addr)(a, b, c, d)

void
sum(FILE *fd, char *name)
{
	byte *buf;
	byte digest[16];
	char pr64[25];
	int i, n;
	MD5state *s;

	s = FGASLR_NIL;
	n = 0;
	buf = FGASLR_CALLOC(256,64);
	for(;;){
		i = FGASLR_FREAD(buf+n, 1, 128*64-n, fd);
		if(i <= 0)
			break;
		n += i;
		if(n & 0x3f)
			continue;
		s = FGASLR_MD5(buf, n, 0, s);
		n = 0;
	}
	FGASLR_MD5(buf, n, digest, s);
	if(FGASLR_HEX){
		for(i=0;i<16;i++) FGASLR_PRINTF("%.2X", digest[i]);
	}else{
		FGASLR_ENC64(pr64,digest,sizeof(digest));
		pr64[22] = '\0';  /* chop trailing == */
		FGASLR_PRINTF("%s",pr64);
	}
	if(name)
		FGASLR_PRINTF("\t%s", name);
	FGASLR_PRINTF("\n");
	FGASLR_FREE(buf);
}
