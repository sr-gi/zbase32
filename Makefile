CPPFLAGS=-Iinclude

.PHONY: all test

all: test

test: src/tests
	./src/tests

src/tests: src/binary.o src/zbase32.o
