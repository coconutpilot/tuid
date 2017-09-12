#CPPFLAGS += -DNDEBUG
CPPFLAGS += -I.
CFLAGS    = -g -Wall -MMD -pthread
LDFLAGS   = -pthread

.PHONY: clean test testvalgrind example examplevalgrind tags

TEST_SOURCES  = $(sort $(wildcard t/*.c))
TEST_PROGRAMS = $(patsubst %.c,%,$(TEST_SOURCES))
TEST_TARGETS  = $(patsubst %.c,%.test,$(TEST_SOURCES))
TEST_VALGRIND = $(patsubst %.c,%.vgtest,$(TEST_SOURCES))

EXAMPLE_SOURCES  = $(sort $(wildcard example/*.c))
EXAMPLE_PROGRAMS = $(patsubst %.c,%,$(EXAMPLE_SOURCES))
EXAMPLE_TARGETS  = $(patsubst %.c,%.example,$(EXAMPLE_SOURCES))
EXAMPLE_VALGRIND = $(patsubst %.c,%.vgexample,$(EXAMPLE_SOURCES))

all: libtuid.so $(TEST_PROGRAMS) $(EXAMPLE_PROGRAMS)

$(TEST_PROGRAMS): libtuid.so t/tap/tap.o

$(EXAMPLE_PROGRAMS): libtuid.so

libtuid.so: tuid.o
	cc $(CFLAGS) -shared -o $@.1.0 $^ -lc -lrt 
	ln -fs $@.1.0 $@.1
	ln -fs $@.1   $@

tuid.o: CFLAGS += -fPIC

test: $(TEST_TARGETS)

example: $(EXAMPLE_TARGETS)

testvalgrind: $(TEST_VALGRIND)

examplevalgrind: $(EXAMPLE_VALGRIND)

%.test: %
	LD_LIBRARY_PATH=. $<

%.example: %
	LD_LIBRARY_PATH=. $<

%.vgtest: %
	LD_LIBRARY_PATH=. valgrind --track-origins=yes --leak-check=full $<

%.vgexample: %
	LD_LIBRARY_PATH=. valgrind --track-origins=yes --leak-check=full $<

tags:
	ctags -R

# self cleaning target from Mischa Sandberg
clean:
	@rm -rf $(shell $(MAKE) -nps all test testvalgrind | sed -n '/^# I/,$${/^[^\#\[%.][^ %]*: /s/:.*//p;}') \
		libtuid.so.* tags gmon.out *.gcov *.prof tmp \
		coverage_html *.info \
		$(filter %.d,$(MAKEFILE_LIST))
	find . -type f -name *.gcda -delete
	find . -type f -name *.gcno -delete


cover: CFLAGS  += --coverage -fprofile-arcs -ftest-coverage
cover: LDFLAGS += --coverage -fprofile-arcs -ftest-coverage
cover: clean test
	lcov -c -d . -o tuid.info --no-recursion
	genhtml -o coverage_html tuid.info
#	gcov -bcp tuid.c


# Run this target to see what the CPP did
%.i: %.c
	$(COMPILE.c) -E $< -o $@


# Remove an implicit rule that shortcuts from .c to executable, this causes breakage in other
# implicit rules that expect a .o to be generated
%: %.c

# Don't rm intermediate files
.SECONDARY:

-include $(shell find . -name '*.d')
