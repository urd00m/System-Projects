CFLAGS=-Wall -g
LIBS=-I$(INC) -L.
INC=includes


all: call_malloc.o
	cc $(CLFAGS) -o call_malloc.out $^

call_malloc.o: call_malloc.c $(INC)/*.h
	cc $(CLFAGS) -c $^ $(LIBS)

test: all
	./call_malloc.out

libmallochijack.so: libmallochijack.c $(INC)/*.h
	cc $(CFLAGS) -fPIC -shared -o $@ $^ $(LIBS) -ldl

rootkit1.so: rkit1.c $(INC)/*.h
	cc $(CLFAGS) -fPIC -shared -o $@ $^ $(LIBS) -ldl

clean:
	touch c.so
	touch c.out
	touch c.o
	rm *.o
	rm *.out
	rm *.so

