#
# qmgetmailaddr - Provice list of email users on a system based on qmail mta.
#
# Copyright (C) 2006-2018 Preben Holm Tønnessen
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC=gcc
OPTS=-g -O2
LIBS=-I$(PWD)/include/
CFLAGS=-std=c99 -W -Wall -Wmissing-prototypes -Wformat -c
LFLAGS=-std=c99 -W -Wall -Wmissing-prototypes -Wformat -o qmgetmailaddr -Xlinker
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
