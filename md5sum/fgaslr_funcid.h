
enum funcid {

	// self
	FUNC_MAIN,
	FUNC_ENCODE,
	FUNC_DECODE,
	FUNC_SUM,
	FUNC_MD5SUM,
	FUNC_INIT64,
	FUNC_ENC64,
	FUNC_DEC64,
	FUNC_MD5,

	FUNC_DEBUG,
	FUNC_HEX,
	FUNC_T64E,
	FUNC_T64D,
	FUNC_TAB,
	FUNC_NIL,

	// libc
	FUNC_PRINTF,
	FUNC_STRCMP,
	FUNC_MEMSET,
	FUNC_CALLOC,
	FUNC_FREE,
	FUNC_FOPEN,
	FUNC_FCLOSE,
	FUNC_FPRINTF,
	FUNC_FREAD,
	FUNC_STDIN,
	FUNC_STDERR,

	FUNC_END = 0xffff,

};
