BINNAME = client
IP ?= 127.0.0.1
PORT ?= 5555
TIME ?= 30
PREFIX = `pwd`/../lib/
INCLUDE = `pwd`/../include/
CFLAGS += -I ${INCLUDE}
LDFLAGS += -L ${PREFIX}
LIBLAGS += -lclient -lsqlite3
CC = gcc

all: clean
	${CC} main.c -o ${BINNAME} ${CFLAGS} ${LDFLAGS} ${LIBLAGS}

clean:
	rm -f ${BINNAME}

distclean: clean
	rm -f *.log
	rm -f *.db

run:
	export PATH=$$PATH:`pwd`;export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${PREFIX};${BINNAME} -i ${IP} -p ${PORT} -t ${TIME} -b
