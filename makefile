CC=gcc
CFLAGS=-Wall -ansi -g
LDFLAGS=

lzw: link.o mapen.o mapde.o map.o

.PHONY: clean
clean:
	rm -rf lzw *.o