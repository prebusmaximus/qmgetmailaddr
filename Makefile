CC=gcc
OPTS=-g -O2
LIBS=-I$(PWD)/include/
CFLAGS=-mcpu=i386 -std=c99 -W -Wall -Wmissing-prototypes -Wformat -c
LFLAGS=-mcpu=i386 -std=c99 -W -Wall -Wmissing-prototypes -Wformat -o qmgetmailaddr -Xlinker
PREFIX=/usr
DESTDIR=$(PREFIX)/bin

all:
	@cd src/ && \
	for file in `ls -1 *.c`; do \
		echo "${CC} ${OPTS} ${LIBS} ${CFLAGS} $$file"; \
		(${CC} ${OPTS} ${LIBS} ${CFLAGS} $$file); \
	done; \
	cd ..
	@echo "${CC} ${OPTS} ${LIBS} ${LFLAGS} ./src/*.o"; \
	${CC} ${OPTS} ${LIBS} ${LFLAGS} ./src/*.o;	

distclean: clean

clean:
	-rm -f qmgetmailaddr ./src/*.o

install:
	install -d $(DESTDIR)
	install qmgetmailaddr $(DESTDIR)

uninstall:
	-rm -f $(DESTDIR)/qmgetmailaddr
