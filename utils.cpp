#include "utils.h"

size_t digitCount(size_t n) {
	if (n == 0) return 1;
	return 1 + floor(log10(n));
}

size_t tabOffset(const std::string &x, size_t end) {
	size_t stop = end == std::string::npos ? x.length() : end;
	size_t length = 0;
	for (size_t i = 0; i < stop; ++i) {
		if (x[i] == '\t') {
			length += 4 - (length % 4) - 1;
		} ++length;
	}
	return length - stop;
}

std::string convertTabs(const std::string &x) {
	std::string result;
	size_t length = 0;
	for (const char &c : x) {
		if (c == '\t') {
			size_t spaces = 4 - (length % 4);
			result += std::string(spaces, ' ');
			length += spaces;
		} else {
			result += c;
			++length;
		}
	}
	return result;
}
