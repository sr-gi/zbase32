CPPFLAGS=-Iinclude

.PHONY: all test

all: test

clean:
	find . -name \*.o -exec rm {} \;
	rm -f src/tests

test: src/tests
	./src/tests

src/tests: src/binary.o src/zbase32.o
