LIBNAME = client
INSTLIB = `pwd`/../lib/
CC = gcc

all: clean shared_lib
	make install

shared_lib:
	${CC} -shared -fPIC *.c -o lib${LIBNAME}.so

static_lib:
	${CC} -c *.c
	ar -rcs lib${LIBNAME}.a *.o

install:
	mkdir -p ${INSTLIB} 
	cp -f lib${LIBNAME}.so ${INSTLIB}

uninstall:
	rm -f ${INSTLIB}/lib${LIBNAME}.*
	rm -r ${INSTLIB}

clean:
	rm -f *.o
	rm -f lib${LIBNAME}.*
