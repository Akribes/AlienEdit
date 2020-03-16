PREFIX = /usr

CXX = g++
CC = g++
CXXFLAGS = -std=c++11 -g $(shell pkg-config --cflags ncurses) -Wall
LDLIBS = $(shell pkg-config --libs ncurses)

alienedit: alienedit.o utils.o menubar.o statusbar.o component.o editor.o linenumbers.o

.PHONY: clean install uninstall
clean:
	rm alienedit.o utils.o menubar.o statusbar.o component.o editor.o linenumbers.o alienedit

install: alienedit
	install alienedit $(PREFIX)/bin/alienedit
	ln -s -f $(PREFIX)/bin/alienedit $(PREFIX)/bin/aled

uninstall:
	unlink $(PREFIX)/bin/aled
	rm -f $(PREFIX)/bin/alienedit
