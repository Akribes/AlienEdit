#ifndef COMPONENT_H
#define COMPONENT_H

#include "utils.h"
#include <ncurses.h>

class AlienEdit; // Can't include alienedit.h

class Component {
	public:
		explicit Component(AlienEdit &parent, Vector2 position, Vector2 size);
		virtual ~Component();

		virtual void refresh() {};
		void resize(Vector2 newPosition, Vector2 newSize);
		void destroy();

	protected:
		AlienEdit &ae;
		WINDOW *win;
		Vector2 pos;
		Vector2 size;
};

#endif // COMPONENT_H
