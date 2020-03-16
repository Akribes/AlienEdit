#ifndef EDITOR_H
#define EDITOR_H

#include "component.h"
#include <ncurses.h>
#include <vector>
#include <string>

class Editor: public Component {
	public:
		Editor(Vector2 position, Vector2 size, std::vector<std::string>* buffer);
		void refresh(bool force = false);
		void focus();
		int acceptInput(bool menuActive);

		Vector2 getStart();
		Vector2 getCursor();

	private:
		Vector2 start;
		Vector2 cursor;

		std::vector<std::string>* buf;
		size_t taboffset();
};

#endif // EDITOR_H
