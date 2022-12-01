.PHONY: clean

CFLAGS=-Wall -g

all: driver exec

driver: driver.o rbtree.o

exec:
	./driver

clean:
	rm -f driver *.o
