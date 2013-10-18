CFLAGS = -g -Wall -DWARNINGS -MMD
CFLAGS += -I.

.PHONY: clean test testvalgrind

TEST_SOURCES  = $(wildcard t/*.c)
TEST_PROGRAMS = $(patsubst %.c,%,$(TEST_SOURCES))
TEST_TARGETS  = $(patsubst %.c,%.test,$(TEST_SOURCES))
TEST_VALGRIND = $(patsubst %.c,%.vgtest,$(TEST_SOURCES))

all: libtuid.so $(TEST_PROGRAMS)

$(TEST_PROGRAMS): libtuid.so t/tap/tap.o

libtuid.so: tuid.o
	ld -shared -soname $@.1 -o $@.1.0 $^ -lc -lrt
	ln -fs $@.1.0 $@.1
	ln -fs $@.1   $@

tuid.o: CFLAGS += -fPIC

test: $(TEST_TARGETS)

testvalgrind: $(TEST_VALGRIND)

%.test: %
	LD_LIBRARY_PATH=. $<

%.vgtest: %
	LD_LIBRARY_PATH=. valgrind --track-origins=yes $<

# self cleaning target from Mischa Sandberg
clean:
	@rm -rf $(shell $(MAKE) -nps all test testvalgrind | sed -n '/^# I/,$${/^[^\#\[%.][^ %]*: /s/:.*//p;}') \
		libtuid.so.*  gmon.out *.gcda *.gcno *.gcov *.prof \
		$(filter %.d,$(MAKEFILE_LIST))

-include $(shell find . -name '*.d')
