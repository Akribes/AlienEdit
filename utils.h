#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <string>

struct Vector2 {
	size_t x;
	size_t y;
	Vector2(): x(0), y(0) {};
	Vector2(size_t x, size_t y): x(x), y(y) {}
};

size_t digitCount(size_t n);
size_t tabOffset(const std::string &x, size_t end = std::string::npos);
std::string convertTabs(const std::string &x);

#endif // UTILS_H
