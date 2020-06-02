CC=gcc
CFLAGS=-I
EXECUTABLE=btest

btreemake: 
	$(CC) main.c data_type.c btree.c -o $(EXECUTABLE)
