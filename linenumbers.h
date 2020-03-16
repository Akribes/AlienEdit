#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include "component.h"
#include <ncurses.h>
#include <vector>

class LineNumbers: public Component {
	public:
		LineNumbers(Vector2 position, Vector2 size, std::vector<std::string> *buffer);
		void refresh(bool force = false);
	
	private:
		size_t start;
		size_t current;
		std::vector<std::string> *buf;
};

#endif // LINENUMBERS_H
