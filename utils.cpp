#include "alienedit.h"

int digitCount(int n) {
	if (n == 0) return 1;
	return 1 + floor(log10(n));
}
