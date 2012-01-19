
cc := gcc
cflags := -Wall -g -I./include

src/%.c:
	$@

tests/%.c:
	$@

include/%.h:
	$@

headers :=\
	include/btree.h\
	include/helpers.h

objects :=\
		build/btree.o\
		build/compare.o\
		build/insert.o\
		build/remove.o\
		build/toarray.o

tests :=\
	build/tests/01-ints\
	build/tests/02-ints\
	build/tests/03-strings

shared := build/btree.so

all: $(shared) $(tests)

build/btree.so: $(objects)
	$(cc) $(cflags) -shared $(objects) -o build/btree.so

build/btree.o: src/btree.c $(headers)
	$(cc) $(cflags) src/btree.c -c -o $@

build/compare.o: src/compare.c $(headers)
	$(cc) $(cflags) src/compare.c -c -o $@

build/insert.o: src/insert.c $(headers)
	$(cc) $(cflags) src/insert.c -c -o $@

build/remove.o: src/remove.c $(headers)
	$(cc) $(cflags) src/remove.c -c -o $@

build/toarray.o: src/toarray.c $(headers)
	$(cc) $(cflags) src/toarray.c -c -o $@

build/tests/01-ints: $(shared) tests/01-ints.c
	$(cc) $(cflags) $(objects) tests/01-ints.c -o $@

build/tests/02-ints: $(shared) tests/02-ints.c
	$(cc) $(cflags) $(objects) tests/02-ints.c -o $@

build/tests/03-strings: $(shared) tests/03-strings.c
	$(cc) $(cflags) $(objects) tests/03-strings.c -o $@

clean:
	rm -f $(objects)
	rm -f build/btree.so
	rm -f $(tests)
