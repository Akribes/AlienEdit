#ifndef COMPONENT_H
#define COMPONENT_H

#include <ncurses.h>
#include "utils.h"

class Component {
	public:
		explicit Component(Vector2 position, Vector2 size);
		virtual ~Component();

		virtual void refresh(bool force = false) = 0;
		void resize(Vector2 newPosition, Vector2 newSize);

	protected:
		WINDOW *win;
		Vector2 pos;
		Vector2 size;
};

#endif // COMPONENT_H
