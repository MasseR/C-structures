CFLAGS=-ggdb3 -Wall
LIBS=-lcgreen
LDFLAGS=$(CFLAGS) $(LIBS)

all: test

structures.la: heap.o
	ar rcs $@ heap.o

heap.o: heap.h
heap.o: heap.c

test: structures.la test.c

runtest: test
	./test

.PHONY: clean

clean:
	rm test
