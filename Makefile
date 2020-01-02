CXX = g++
CC = g++
CXXFLAGS = -g $(shell pkg-config --cflags ncurses)
LDFLAGS = $(shell pkg-config --libs ncurses)

alienedit: alienedit.o
