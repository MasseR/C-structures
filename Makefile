CFLAGS=-ggdb3 -Wall
LIBS=-lcgreen
LDFLAGS=$(CFLAGS) $(LIBS)
all: test

test: test.c

runtest: test
	./test
