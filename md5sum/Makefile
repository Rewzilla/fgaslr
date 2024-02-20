
CFLAGS		+= -I./ -DENABLE_GRAPH

# silence warnings from the project code itself, meh
CFLAGS		+= -Wno-char-subscripts -Wno-unused-function -Wno-unused-variable

all:
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_dec64.o md5sum_dec64.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_decode.o md5sum_decode.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_enc64.o md5sum_enc64.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_encode.o md5sum_encode.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_init64.o md5sum_init64.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_main.o md5sum_main.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_md5.o md5sum_md5.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_sum.o md5sum_sum.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_debug.o md5sum_debug.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_hex.o md5sum_hex.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_t64e.o md5sum_t64e.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_t64d.o md5sum_t64d.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_tab.o md5sum_tab.c
	$(CC) $(CFLAGS) $(LIBS) -c -o md5sum_nil.o md5sum_nil.c

	$(CC) $(CFLAGS) $(LIBS) -g -o md5sum.bin md5sum.c \
		../src/fgaslr.c -D'PROG_NAME="md5sum"' ../src/start.c \
		../src/cache.c ../src/mappings.c ../src/graph.c ../src/stats.c

clean:

	rm *.o *.bin