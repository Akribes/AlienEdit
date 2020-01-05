CXX = g++
CC = g++
CXXFLAGS = -std=c++11 -g $(shell pkg-config --cflags ncurses)
LDFLAGS = $(shell pkg-config --libs ncurses)

alienedit: alienedit.o utils.o
