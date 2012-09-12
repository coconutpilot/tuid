#CFLAGS=-g

.PHONY: clean

all: test1 test2

libtuid.so: tuid.o
	ld -shared -soname $@.1 -o $@.1.0 tuid.o -lc -lrt
	ln -s ./libtuid.so.1.0 libtuid.so.1
	ln -s ./libtuid.so.1   libtuid.so

tuid.o: tuid.c tuid.h
	gcc -fPIC -c $<

test: test1 test2
	LD_LIBRARY_PATH=. ./test1
	LD_LIBRARY_PATH=. ./test2

test1: test1.c libtuid.so
	gcc -o test1 test1.c -L. -ltuid

test2: test2.c libtuid.so
	gcc -o test2 test2.c -L. -ltuid

clean:
	rm -f *.so* *.o test1 test2
# DO NOT DELETE
