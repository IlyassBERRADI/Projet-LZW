CC=gcc
CFLAGS=-Wall -g
LDFLAGS=

# Create the executable, and compile all modified C files into binaries
# before creating the executable.
lzw: bit_io.o link.o mapen.o mapde.o map.o str.o

.PHONY: clean
clean:
	rm -rf lzw *.o