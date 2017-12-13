CC=mpicc
CFLAGS=-I.
all: hello p2p collect

hello: hello.o
	$(CC) -o hello hello.o -I.
p2p: p2p.o
	$(CC) -o p2p p2p.o -I.
collect: collect.o
	$(CC) -o collect collect.o -I.