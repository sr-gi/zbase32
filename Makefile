CFLAGS=-O3 -ansi -pedantic -Wall -pipe
CPPFLAGS=-Iinclude

.PHONY: all clean lib test

all: test

clean:
	find . \( -name \*.o -o -name \*.pyc \) -exec rm {} \;
	rm -rf MANIFEST __pycache__ dist build src/tests

test: src/tests
	./src/tests

src/tests: src/binary.o src/zbase32.o
