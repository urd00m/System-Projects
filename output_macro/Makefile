CLFAGS=-Wall -g
LIBS=-I. -L.

all: main.o
	cc -o main.out main.o $(CLFAGS) $(LIBS)

main.o: main.c urd00m_output.h
	cc -c $^ $(CFLAGS)

clean:
	touch bye.out
	touch bye.o
	rm *.out
	rm *.o

test: all
	./main.out
