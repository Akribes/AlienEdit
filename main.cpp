#include "alienedit.h"
#include <string>

int main(int argc, char **argv) {
	std::string fileName (argc > 1 ? argv[1] : "");
	AlienEdit(fileName).start();
	return 0;
}
