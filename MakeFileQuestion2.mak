all:
	gcc -w -o FIFO_A Question2FIFO_A.c
	gcc -w -o FIFO_B Question2FIFO_B.c

	./FIFO_B
