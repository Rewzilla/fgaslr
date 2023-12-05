
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_SELF, FUNC_ENCODE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_DECODE), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_TAB), NULL},
	{FGASLR_ENTRY(LIB_SELF, FUNC_NIL), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_CALLOC), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_FREE), NULL},
	{FGASLR_ENTRY(LIB_LIBC, FUNC_MEMSET), NULL},
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

#define FGASLR_ENCODE(a, b, c) ((void (*)(byte *, uint *,uint))funcs[0].addr)(a, b, c)
#define FGASLR_DECODE(a, b, c) ((void (*)(uint *, byte *,uint))funcs[1].addr)(a, b, c)
#define FGASLR_TAB ((Table *)funcs[2].addr)
#define FGASLR_NIL (*(MD5state **)funcs[3].addr)
#define FGASLR_CALLOC(a, b) ((void * (*)(size_t,size_t))funcs[4].addr)(a, b)
#define FGASLR_FREE(a) ((void (*)(void *))funcs[5].addr)(a)
#define FGASLR_MEMSET(a, b, c) ((void * (*)(void *,int,size_t))funcs[6].addr)(a, b, c)

/*
 *  I require len to be a multiple of 64 for all but
 *  the last call
 */
MD5state*
md5(byte *p, uint len, byte *digest, MD5state *s)
{
	uint a, b, c, d, tmp;
	uint i, done;
	Table *t;
	byte *end;
	uint x[16];

	if(s == FGASLR_NIL){
		s = FGASLR_CALLOC(sizeof(*s),1);
		if(s == FGASLR_NIL)
			return FGASLR_NIL;

		/* seed the state, these constants would look nicer big-endian */
		s->state[0] = 0x67452301;
		s->state[1] = 0xefcdab89;
		s->state[2] = 0x98badcfe;
		s->state[3] = 0x10325476;
	}
	s->len += len;

	i = len & 0x3f;
	if(i || len == 0){
		done = 1;

		/* pad the input, assume there's room */
		if(i < 56)
			i = 56 - i;
		else
			i = 120 - i;
		if(i > 0){
			FGASLR_MEMSET(p + len, 0, i);
			p[len] = 0x80;
		}
		len += i;

		/* append the count */
		x[0] = s->len<<3;
		x[1] = s->len>>29;
		FGASLR_ENCODE(p+len, x, 8);
	} else
		done = 0;

	for(end = p+len; p < end; p += 64){
		a = s->state[0];
		b = s->state[1];
		c = s->state[2];
		d = s->state[3];

		FGASLR_DECODE(x, p, 64);

		for(i = 0; i < 64; i++){
			t = FGASLR_TAB + i;
			switch(i>>4){
			case 0:
				a += (b & c) | (~b & d);
				break;
			case 1:
				a += (b & d) | (c & ~d);
				break;
			case 2:
				a += b ^ c ^ d;
				break;
			case 3:
				a += c ^ (b | ~d);
				break;
			}
			a += x[t->x] + t->sin;
			a = (a << t->rot) | (a >> (32 - t->rot));
			a += b;
	
			/* rotate variables */
			tmp = d;
			d = c;
			c = b;
			b = a;
			a = tmp;
		}

		s->state[0] += a;
		s->state[1] += b;
		s->state[2] += c;
		s->state[3] += d;
	}

	/* return result */
	if(done){
		FGASLR_ENCODE(digest, s->state, 16);
		FGASLR_FREE(s);
		return FGASLR_NIL;
	}
	return s;
}

