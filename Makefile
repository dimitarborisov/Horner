CC=gcc


horner: horner.c
	$(CC) horner.c -o horner

clean:
	rm -f horner
 
