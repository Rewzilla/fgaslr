
#include "md5sum_types.h"

#include "../src/fgaslr.h"

__attribute__((section(".lot")))
long int got = 1;

__attribute__((section(".lot")))
struct func funcs[] = {
	{FGASLR_ENTRY(LIB_END, FUNC_END), NULL},
};

Table tab[] =
{
	/* round 1 */
	{ 0xd76aa478, 0, S11},	
	{ 0xe8c7b756, 1, S12},	
	{ 0x242070db, 2, S13},	
	{ 0xc1bdceee, 3, S14},	
	{ 0xf57c0faf, 4, S11},	
	{ 0x4787c62a, 5, S12},	
	{ 0xa8304613, 6, S13},	
	{ 0xfd469501, 7, S14},	
	{ 0x698098d8, 8, S11},	
	{ 0x8b44f7af, 9, S12},	
	{ 0xffff5bb1, 10, S13},	
	{ 0x895cd7be, 11, S14},	
	{ 0x6b901122, 12, S11},	
	{ 0xfd987193, 13, S12},	
	{ 0xa679438e, 14, S13},	
	{ 0x49b40821, 15, S14},

	/* round 2 */
	{ 0xf61e2562, 1, S21},	
	{ 0xc040b340, 6, S22},	
	{ 0x265e5a51, 11, S23},	
	{ 0xe9b6c7aa, 0, S24},	
	{ 0xd62f105d, 5, S21},	
	{  0x2441453, 10, S22},	
	{ 0xd8a1e681, 15, S23},	
	{ 0xe7d3fbc8, 4, S24},	
	{ 0x21e1cde6, 9, S21},	
	{ 0xc33707d6, 14, S22},	
	{ 0xf4d50d87, 3, S23},	
	{ 0x455a14ed, 8, S24},	
	{ 0xa9e3e905, 13, S21},	
	{ 0xfcefa3f8, 2, S22},	
	{ 0x676f02d9, 7, S23},	
	{ 0x8d2a4c8a, 12, S24},

	/* round 3 */
	{ 0xfffa3942, 5, S31},	
	{ 0x8771f681, 8, S32},	
	{ 0x6d9d6122, 11, S33},	
	{ 0xfde5380c, 14, S34},	
	{ 0xa4beea44, 1, S31},	
	{ 0x4bdecfa9, 4, S32},	
	{ 0xf6bb4b60, 7, S33},	
	{ 0xbebfbc70, 10, S34},	
	{ 0x289b7ec6, 13, S31},	
	{ 0xeaa127fa, 0, S32},	
	{ 0xd4ef3085, 3, S33},	
	{  0x4881d05, 6, S34},	
	{ 0xd9d4d039, 9, S31},	
	{ 0xe6db99e5, 12, S32},	
	{ 0x1fa27cf8, 15, S33},	
	{ 0xc4ac5665, 2, S34},	

	/* round 4 */
	{ 0xf4292244, 0, S41},	
	{ 0x432aff97, 7, S42},	
	{ 0xab9423a7, 14, S43},	
	{ 0xfc93a039, 5, S44},	
	{ 0x655b59c3, 12, S41},	
	{ 0x8f0ccc92, 3, S42},	
	{ 0xffeff47d, 10, S43},	
	{ 0x85845dd1, 1, S44},	
	{ 0x6fa87e4f, 8, S41},	
	{ 0xfe2ce6e0, 15, S42},	
	{ 0xa3014314, 6, S43},	
	{ 0x4e0811a1, 13, S44},	
	{ 0xf7537e82, 4, S41},	
	{ 0xbd3af235, 11, S42},	
	{ 0x2ad7d2bb, 2, S43},	
	{ 0xeb86d391, 9, S44},	
};
