HEADERS = 
CFLAGS = -g -Wall

default: microsim

microsim.o: microsim.c $(HEADERS)
	gcc $(CFLAGS) -c microsim.c -o microsim.o

microsim: microsim.o
	gcc microsim.o -o microsim

clean:
	-rm -f microsim.o
	-rm -f microsim
