CC=gcc
CFLAGS=-march=native

bsdsay: bsdsay.c
	$(CC) $(CFLAGS) bsdsay.c -o bsdsay

clean: bsdsay
	rm bsdsay
