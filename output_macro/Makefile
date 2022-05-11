CLFAGS=-Wall -g
INC=includes
LIBS=-I$(INC) -L.

all: main.o
	cc -o main.out main.o $(CLFAGS) $(LIBS)

main.o: main.c $(INC)/*.h
	cc -c $^ $(CFLAGS) $(LIBS)

clean:
	touch bye.out
	touch bye.o
	rm *.out
	rm *.o

menuconfig:
	@scripts/menuconfig.py

cfg:
	@scripts/menuconfig.py

test: all
	./main.out
