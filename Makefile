CFLAGS=-g -Wall -DWARNINGS

.PHONY: clean

all: test1 test2 test3 test4 test5 test6

libtuid.so: tuid.o
	ld -shared -soname $@.1 -o $@.1.0 tuid.o -lc -lrt
	ln -s ./libtuid.so.1.0 libtuid.so.1
	ln -s ./libtuid.so.1   libtuid.so

tuid.o: tuid.c tuid.h
	gcc $(CFLAGS) -fPIC -c $<

test: test1 test2 test3 test4 test5 test6
	LD_LIBRARY_PATH=. ./test1
	LD_LIBRARY_PATH=. ./test2
	LD_LIBRARY_PATH=. ./test3
	LD_LIBRARY_PATH=. ./test4
	LD_LIBRARY_PATH=. ./test5
	LD_LIBRARY_PATH=. ./test6

test1: test1.c libtuid.so
	gcc $(CFLAGS) -o test1 test1.c -L. -ltuid

test2: test2.c libtuid.so
	gcc $(CFLAGS) -o test2 test2.c -L. -ltuid

test3: test3.c libtuid.so
	gcc $(CFLAGS) -o test3 test3.c -L. -ltuid

test4: test4.c libtuid.so
	gcc $(CFLAGS) -o test4 test4.c -L. -ltuid

test5: test5.c libtuid.so
	gcc $(CFLAGS) -o test5 test5.c -L. -ltuid

test6: test6.c libtuid.so
	gcc $(CFLAGS) -o test6 test6.c -L. -ltuid

clean:
	rm -f *.so* *.o test1 test2 test3 test4 test5 test6
# DO NOT DELETE
