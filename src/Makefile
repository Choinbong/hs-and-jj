CFLAGS=-Wall -g

# driver: driver.o rbtree.o

# test makefile start

driver: driver.o new_rbtree.o rbtree_insert_fixup.o rbtree_insert.o rbtree_rotate.o rbtree_to_array.o
	gcc -o driver driver.o rbtree_new_rbtree.o rbtree_insert_fixup.o rbtree_insert.o rbtree_rotate.o rbtree_to_array.o
	

new_rbtree.o:
	gcc -c ./func/rbtree_new_rbtree.c

rbtree_insert_fixup.o:
	gcc -c ./func/rbtree_insert_fixup.c

rbtree_insert.o:
	gcc -c ./func/rbtree_insert.c

rbtree_rotate.o:
	gcc -c ./func/rbtree_rotate.c

rbtree_to_array.o:
	gcc -c ./func/rbtree_to_array.c

#test makefile end

clean:
	rm -f driver *.o
