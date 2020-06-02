CC=gcc
CFLAGS=-I

btreemake: 
	$(CC) main.c data_type.c btree.c -o btest
