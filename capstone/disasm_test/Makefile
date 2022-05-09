CFLAGS =-g -Wall #-Werror #-Wl,-rpath,$(shell pwd)
LIBS = -L. -I. -lcapstone

all: main.o
	cc -o main.out main.o $(CLFAGS) $(LIBS)

main.o: main.c 
	cc -c main.c $(CFLAGS)

clean: 
	rm *.o
	rm *.out

test: all
	./main.out
