CFLAGS=-g -Wall -DWARNINGS
CFLAGS=-g -Wall

.PHONY: clean

TEST_TARGETS = $(patsubst %.c,%,$(wildcard t/*.c))

all: libtuid.so $(TEST_TARGETS)

$(TEST_TARGETS): libtuid.so
	gcc $(CFLAGS) $@.c -o $@ -I. -L. -ltuid

libtuid.so: tuid.o
	ld -shared -soname $@.1 -o $@.1.0 tuid.o -lc -lrt
	ln -s ./libtuid.so.1.0 libtuid.so.1
	ln -s ./libtuid.so.1   libtuid.so

tuid.o: tuid.c tuid.h
	gcc $(CFLAGS) -I. -fPIC -c $<

test: $(TEST_TARGETS)
	LD_LIBRARY_PATH=. $^

clean:
	rm -f *.so* *.o $(TEST_TARGETS)
