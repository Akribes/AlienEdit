#ifndef EDITOR_H
#define EDITOR_H

#include "component.h"
#include <ncurses.h>
#include <vector>
#include <string>

class Editor: public Component {
	public:
		Editor(AlienEdit &parent, Vector2 position, Vector2 size, std::vector<std::string> &buffer);
		void refresh();
		void focus();
		int acceptInput(bool menuActive);

		Vector2 getStart();
		Vector2 getCursor();

		void toggleSelect();
		bool isSelecting();
		bool hasClipboard();
		void copy();
		void cut();
		void paste();

	private:
		Vector2 start;
		Vector2 cursor;

		bool selecting = false;
		bool clipboard = false;
		Vector2 selection;

		std::vector<std::string> &buf;
		size_t taboffset();
};

#include "alienedit.h"

#endif // EDITOR_H
