
# silence warnings from the project code itself, meh
CFLAGS		+= -Wno-char-subscripts -Wno-unused-function -Wno-unused-variable -Wno-main

all:

	$(CC) $(CFLAGS) $(LIBS) -g -o md5sum.bin md5sum.c

clean:

	rm *.bin
