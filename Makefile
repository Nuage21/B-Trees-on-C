CC=gcc
CFLAGS=-I
EXECUTABLE=btest

all: btree.o data_type.o main.o 
	$(CC) btree.o data_type.o main.o -o $(EXECUTABLE)

btree.o: btree.c
	$(CC) -c btree.c

data_type.o: data_type.c
	$(CC) -c data_type.c

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o $(EXECUTABLE)