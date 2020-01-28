#ifndef UTILS_H
#define UTILS_H

#include <cmath>

struct Position {
	unsigned x;
	unsigned y;
	Position(unsigned x, unsigned y): x(x), y(y) {}
};

int digitCount(int n);

#endif // UTILS_H
