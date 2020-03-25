#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include "component.h"
#include <ncurses.h>
#include <vector>

class LineNumbers: public Component {
	public:
		LineNumbers(AlienEdit &parent, Vector2 position, Vector2 size, std::vector<std::string> &buffer);
		void refresh();
	
	private:
		size_t start;
		size_t current;
		std::vector<std::string> &buf;
};

#include "alienedit.h"

#endif // LINENUMBERS_H
