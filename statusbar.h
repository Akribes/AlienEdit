#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "component.h"
#include <ncurses.h>
#include <sstream>

class StatusBar: public Component {
	public:
		bool unsavedChanges;

		StatusBar(AlienEdit &parent, Vector2 position, Vector2 size);
		void refresh();
};

#include "alienedit.h"

#endif // STATUSBAR_H
