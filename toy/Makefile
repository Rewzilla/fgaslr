
CFLAGS		+= -I./ -DENABLE_GRAPH

all:

	$(CC) $(CFLAGS) -c -o toy_main.o toy_main.c
	$(CC) $(CFLAGS) -c -o toy_add.o toy_add.c
	$(CC) $(CFLAGS) -c -o toy_mul.o toy_mul.c
	$(CC) $(CFLAGS) -c -o toy_div.o toy_div.c

	$(CC) $(CFLAGS) -g -o toy.bin toy.c \
		../src/fgaslr.c -D'PROG_NAME="toy"' \
		../src/cache.c ../src/mappings.c ../src/graph.c

clean:

	rm *.o *.bin
