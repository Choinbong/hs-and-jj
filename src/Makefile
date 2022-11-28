.PHONY: clean

CFLAGS=-Wall -g

driver: driver.o rbtree.o func/rbtree_insert_fixup.o func/rbtree_insert.o func/rbtree_new_rbtree.o func/rbtree_rotate.o

clean:
	rm -f driver *.o
