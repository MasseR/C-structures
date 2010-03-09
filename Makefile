CFLAGS=-ggdb3 -Wall
LIBS=-lcgreen
LDFLAGS=$(CFLAGS) $(LIBS)

all: test

structures.la: heap.o
structures.la: stack.o
structures.la:
	ar rcs $@ heap.o stack.o

heap.o: heap.h
heap.o: heap.c

stack.o: stack.h
stack.o: stack.c

test: structures.la test.c

runtest: test
	./test

.PHONY: clean

clean:
	rm test *.o *.la
