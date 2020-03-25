#ifndef MENUBAR_H
#define MENUBAR_H

#include "component.h"
#include <ncurses.h>
#include <vector>
#include <utility>
#include <functional>

typedef std::vector<std::pair<std::string, std::function<void ()> > > Menu;

class MenuBar: public Component {
	public:
		size_t selection;
		bool active;

		MenuBar(AlienEdit &parent, Vector2 position, Vector2 size);
		void refresh();
		bool toggle();
		void confirm();
		size_t options();
	private:
		Menu mainMenu;
};

#include "alienedit.h"

#endif // MENUBAR_H
