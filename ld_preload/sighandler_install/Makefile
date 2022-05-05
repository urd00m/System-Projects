#gcc flags:
# -c assemble but do not link
# -g include debug information
# -o output
# -s make stripped libray

# uncomment the last part in line 10 to specify current working
# directory as the default search path for shared objects

CFLAGS =-Wall -fPIC #-Werror #-Wl,-rpath,$(shell pwd) 
LIBS = -L. -I. -lgety2
LDLIBS = -pthread -ldl

all: main.o libgety2.so libsig_install.so
	cc -o my_app main.o  $(CFLAGS) $(LIBS)

main.o: main.c
	cc -c main.c $(CFLAGS)

libgety2.so:
	cc -fPIC -shared -dynamiclib libgety2.c -o libgety2.so

libsig_install.so: libsig_install.c
	cc -fPIC -dynamiclib -shared libsig_install.c  -o libsig_install.so $(LDLIBS) $(LIBS)

test: all
	./run.sh

.PHONY: clean
clean:
	rm *.o
	rm *.so
