CPPFLAGS += -DNDEBUG
CPPFLAGS += -I.
CFLAGS    = -g -Wall -MMD -pthread
LDFLAGS   = -pthread

.PHONY: clean test testvalgrind tags

TEST_SOURCES  = $(sort $(wildcard t/*.c))
TEST_PROGRAMS = $(patsubst %.c,%,$(TEST_SOURCES))
TEST_TARGETS  = $(patsubst %.c,%.test,$(TEST_SOURCES))
TEST_VALGRIND = $(patsubst %.c,%.vgtest,$(TEST_SOURCES))

all: libtuid.so $(TEST_PROGRAMS)

$(TEST_PROGRAMS): libtuid.so t/tap/tap.o

libtuid.so: tuid.o
	cc $(CFLAGS) -shared -o $@.1.0 $^ -lc -lrt 
	ln -fs $@.1.0 $@.1
	ln -fs $@.1   $@

tuid.o: CFLAGS += -fPIC

test: $(TEST_TARGETS)

testvalgrind: $(TEST_VALGRIND)

%.test: %
	LD_LIBRARY_PATH=. $<

%.vgtest: %
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
