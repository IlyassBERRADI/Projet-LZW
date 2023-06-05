CC=gcc
CFLAGS=-Wall -ansi -g
LDFLAGS=

# Create the executable, and compile all modified C files into binaries
# before creating the executable.
lzw: link.o mapen.o mapde.o map.o str.o

.PHONY: clean
clean:
	rm -rf lzw *.o